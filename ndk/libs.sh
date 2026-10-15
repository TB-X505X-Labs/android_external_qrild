. ~/ril-build/env.sh
set -e
cd $R
CF="-O2 -fPIC -Wno-error -I$R/libqril -I$R/libqril/lib -I$R/libqril/qmi -I$R/qrtr/lib -idirafter $R/qrtr/src"
mkdir -p obj/qrtr obj/qril
for f in qrtr/lib/*.c; do $CC $CF -c $f -o obj/qrtr/$(basename $f).o; done
$AR rcs libqrtr.a obj/qrtr/*.o
cd libqril/qmi
for q in qril_*.qmi; do $R/qmic/qmic -k -f $q -o . ; done
cd $R/libqril
for f in libqril.c libqril_events.c libqril_services.c libqril_messages.c libqril_qmi.c util.c q_log.c workqueue.c timespec.c lock_tracker.c qmi_tlv.c qmi/qmi_*.c; do $CC $CF -c $f -o $R/obj/qril/$(echo $f | tr / _).o 2>>$R/obj/qril.err || echo "FAIL $f"; done
$CXX $CXXFLAGS $CF -c libqril_client.cc -o $R/obj/qril/client.o 2>>$R/obj/qril.err || echo "FAIL client"
cd $R; $AR rcs libqril.a obj/qril/*.o; ls -l libqrtr.a libqril.a
