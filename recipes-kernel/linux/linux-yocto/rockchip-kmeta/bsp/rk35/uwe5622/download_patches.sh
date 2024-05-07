#!/bin/bash
# Simple scrit to downlload uwe patches from armbian using 
# build/lib/functions/compilation/patch/drivers_network.sh
# function driver_uwe5622()


PREFIX_MISC="https://raw.githubusercontent.com/armbian/build/main/patch/misc/wireless-uwe5622/"
PREFIX_RK="https://raw.githubusercontent.com/armbian/build/main/patch/kernel/archive/rockchip64-6.6/"

if [ $# -lt 1 ] ; then
	echo "usage $0 <scc file>"
        exit 1
fi

while read e ; do

 f=$(echo $e | cut -f 2 -d ' ')

 if echo $f | grep '000' > /dev/null ; then
    echo "Ignore $f"
    continue
 fi

 url="${PREFIX_RK}${f}"
 if echo $f | grep 'wireless-' >/dev/null ; then
   url="${PREFIX_MISC}${f}"
 elif echo $f | grep 'uwe5622-' >/dev/null; then
   url="${PREFIX_MISC}${f}"
 fi
 
 echo "Downloading $f [$url] ..."
 wget "${url}" -O "./$f"

done < <(cat $1 | grep -v ^# | grep '^patch')




