DESCRIPTION = "U-Boot port for pico"
PROVIDES += "u-boot"

require recipes-bsp/u-boot/u-boot.inc

LICENSE = "GPL-2.0-only"
LIC_FILES_CHKSUM = "file://Licenses/gpl-2.0.txt;md5=b234ee4d69f5fce4486a80fdaf4a4263"

COMPATIBLE_MACHINE = "rv1106"

SRC_URI = "\
    git://github.com/LuckfoxTECH/luckfox-pico.git;protocol=https;branch=main;subpath=sysdrv/source/uboot \
    file://env.txt \
    file://RV1106MINIALL.ini \
    file://relocated-environment.cfg \
    file://enable_emmc.cfg \
    ${@bb.utils.contains('DISTRO_FEATURES', 'debug-tweaks', 'boot_delay.cfg', '', d)} \ 
"
SRCREV="1e160dee559c6cb638e3d078b543fbcd2fab9699"


RM_WORK_EXCLUDE += "${PN} "

COMPATIBLE_MACHINE:cura = "(rockchip-rv1106)"

S = "${WORKDIR}/uboot/u-boot"
B = "${WORKDIR}/build"

EXTRA_OEMAKE += " KCFLAGS='-Wno-error=enum-int-mismatch -Wno-error=address -Wno-error=maybe-uninitialized' "
DEPENDS += "bc-native coreutils-native u-boot-tools-native"

inherit pkgconfig deploy

do_configure[cleandirs] = "${B}"

do_compile:append () {
    ${S}/../rkbin/tools/boot_merger ${WORKDIR}/RV1106MINIALL.ini
    mkenvimage -s 8192 -p 0x0 -o env.img ${WORKDIR}/env.txt
}

do_deploy:append () {
    install -D -m 0644 ${B}/rv1106_idblock.img ${DEPLOYDIR}/idblock.img
    install -D -m 0644 ${B}/env.img ${DEPLOYDIR}/u-boot-default-env.img
}

