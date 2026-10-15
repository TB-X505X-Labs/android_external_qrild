#!/usr/bin/env python3
# SPDX-License-Identifier: Apache-2.0
import os
import re
import sys

AIDL = sys.argv[1]
OUT = sys.argv[2]

IFACES = ["config", "data", "messaging", "modem", "network", "sim", "voice"]

PRIM = {
    "int": "int32_t",
    "long": "int64_t",
    "boolean": "bool",
    "byte": "int8_t",
    "char": "char16_t",
    "float": "float",
    "double": "double",
}

enum_cache = {}


def is_enum(fq):
    if fq in enum_cache:
        return enum_cache[fq]
    path = os.path.join(AIDL, *fq.split(".")) + ".aidl"
    res = False
    if os.path.exists(path):
        src = open(path).read()
        res = re.search(r"^\s*(@[\w.()=, ]+\s+)*enum\s", src, re.M) is not None \
            and re.search(r"^\s*(@[\w.()=, ]+\s+)*parcelable\s", src, re.M) is None
    enum_cache[fq] = res
    return res


def cpp_type(t, nullable=False):
    if nullable:
        inner = cpp_type(t)
        inner = inner[len("const "):-1] if inner.startswith("const ") else inner
        return "const std::optional<%s>&" % inner
    arr = t.endswith("[]")
    base = t[:-2] if arr else t
    if base in PRIM:
        inner = "uint8_t" if (arr and base == "byte") else PRIM[base]
        kind = "prim"
    elif base == "String":
        inner, kind = "std::string", "obj"
    else:
        inner = "::aidl::" + base.replace(".", "::")
        if base.split(".")[-1].startswith("I") and base.split(".")[-1][1:2].isupper():
            inner = "std::shared_ptr<%s>" % inner
            kind = "obj"
        else:
            kind = "prim" if is_enum(base) else "obj"
    if arr:
        return "const std::vector<%s>&" % inner
    return inner if kind == "prim" else "const %s&" % inner


def parse(path):
    methods = []
    for line in open(path):
        m = re.match(r"\s*oneway void (\w+)\((.*)\);", line)
        if not m:
            continue
        params = []
        for p in filter(None, [x.strip() for x in m.group(2).split(",")]):
            parts = p.split()
            params.append((parts[-2], parts[-1], "@nullable" in p))
        methods.append((m.group(1), params))
    return methods


def sig(name, params):
    return "::ndk::ScopedAStatus %s(%s)" % (
        name, ", ".join("%s in_%s" % (cpp_type(t, nl), n) for t, n, nl in params))


for iface in IFACES:
    Name = "Radio" + iface.capitalize()
    pkg = "android.hardware.radio." + iface
    ns = "::aidl::" + pkg.replace(".", "::")
    d = os.path.join(AIDL, "android", "hardware", "radio", iface)
    req = parse(os.path.join(d, "I%s.aidl" % Name))
    rsp = {n: p for n, p in parse(os.path.join(d, "I%sResponse.aidl" % Name))}
    o = []
    o.append("// SPDX-License-Identifier: Apache-2.0")
    o.append("#pragma once\n")
    o.append("#include <%s/Bn%s.h>" % (pkg.replace(".", "/").join(["aidl/", ""]), Name))
    o.append("#include <%s/I%sResponse.h>" % (pkg.replace(".", "/").join(["aidl/", ""]), Name))
    o.append("#include <%s/I%sIndication.h>" % (pkg.replace(".", "/").join(["aidl/", ""]), Name))
    o.append('#include "response_info.h"\n')
    o.append("class %sBase : public %s::Bn%s {" % (Name, ns, Name))
    o.append("  protected:")
    o.append("    std::shared_ptr<%s::I%sResponse> mResp;" % (ns, Name))
    o.append("    std::shared_ptr<%s::I%sIndication> mInd;" % (ns, Name))
    o.append("    virtual void onResponseFunctionsSet() {}\n")
    o.append("  public:")
    for name, params in req:
        o.append("    %s override {" % sig(name, params))
        if name == "setResponseFunctions":
            o.append("        mResp = in_%s;" % params[0][1])
            o.append("        mInd = in_%s;" % params[1][1])
            o.append("        onResponseFunctionsSet();")
        elif name + "Response" in rsp and params and params[0][1] == "serial":
            rp = rsp[name + "Response"]
            info = "modemNotSupported" if rp[0][0].endswith("Modem") else "notSupported"
            args = ["%s(in_serial)" % info] + ["{}"] * (len(rp) - 1)
            o.append("        if (mResp) mResp->%sResponse(%s);" % (name, ", ".join(args)))
        o.append("        return ::ndk::ScopedAStatus::ok();")
        o.append("    }")
    o.append("};")
    open(os.path.join(OUT, "%s_base.h" % iface), "w").write("\n".join(o) + "\n")
    print(iface, len(req), "methods")
