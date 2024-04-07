SUMMARY = "Custom rockchip kernel for pico boards from luckfox pico sdk"
SECTION = "kernel"
LICENSE = "GPL-2.0-only"
LIC_FILES_CHKSUM = "file://COPYING;md5=6bc538ed5bd9a7fc9398086aedcd7e46"


inherit kernel
require recipes-kernel/linux/linux-yocto.inc

SRC_URI = "\
     https://github.com/LuckfoxTECH/luckfox-pico/archive/1e160dee559c6cb638e3d078b543fbcd2fab9699.tar.gz;downloadfilename=pico-sdk.tar.gz \
     file://enable_g_ether.cfg \
"
#   This refuse to work so we use the tarball.
#    git://github.com/LuckfoxTECH/luckfox-pico.git;protocol=https;branch=main;subpath=sysdrv/source/kernel \
#SRCREV="1e160dee559c6cb638e3d078b543fbcd2fab9699"
#"
SRC_URI[sha256sum] = "cf15c2c11cef97877309925a28d038dae20520eae43562b1edc503fbd4cd0fad"

LINUX_VERSION ?= "5.10"
LINUX_VERSION_EXTENSION:append = "-custom"

KCONFIG_MODE = "--alldefconfig"
KBUILD_DEFCONFIG := "luckfox_rv1106_linux_defconfig"

KBRANCH = "main"

S = "${WORKDIR}/luckfox-pico-1e160dee559c6cb638e3d078b543fbcd2fab9699/sysdrv/source/kernel"
#PV = "${LINUX_VERSION}+git"

COMPATIBLE_MACHINE = "rv1106"
KERNEL_VERSION_SANITY_SKIP="1"

