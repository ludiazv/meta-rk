#!/bin/sh
#
#Flash bootloader to spi

DST=/dev/mtd0
SRC=/boot/u-boot/u-boot-rockchip-spi.bin

[ -n "$1" ] && SRC=$1
[ -n "$2" ] && DST=$2

echo "This script will erase the spi flash and install the provided bootloader"
echo "source:$SRC destination:$DST"
echo "do you want to proceed [y/N]?"
read -n 1 resp

if [ "$resp" = "y" ] ; then
   echo "Flashing spi $DST..."
   flashcp --version
   flashcp --partition --verbose $SRC $DST
else
   echo "aborted"
fi

