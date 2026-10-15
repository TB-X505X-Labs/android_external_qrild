. ~/ril-build/env.sh
set -e
cd $R/hal
QI="-I$R/libqril -I$R/libqril/lib -I$R/libqril/qmi -I$R/qrtr/lib"
mkdir -p obj
$CC -O2 -fPIC $QI -c src/qmi_glue.c -o obj/qmi_glue.o
$CXX $CXXFLAGS -Isrc $QI -c src/radio.cc -o obj/radio.o
$CXX -o android.hardware.radio-service.qrild obj/radio.o obj/qmi_glue.o $R/libradio_aidl.a $R/libqril.a $R/libqrtr.a -L$R/devlibs -lbinder_ndk -llog -static-libstdc++ -Wl,--allow-shlib-undefined
ls -l android.hardware.radio-service.qrild
