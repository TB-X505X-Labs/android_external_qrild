#!/vendor/bin/sh
T=/data/local/tmp
$T/run $T/alp/usr/bin/rmtfs -o /dev/block/by-name -P -s &
$T/run $T/alp/usr/bin/tqftpserv &
exec /vendor/bin/hw/android.hardware.radio-service.qrild
