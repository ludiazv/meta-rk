DESCRIPTION = "UWE5622 Wifi firmware"
LICENSE = "CC0-1.0"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/${LICENSE};md5=0ceb3372c9595f0a8067e55da801e4a1"


COMPATIBLE_MACHINE = "orangepi-3b"

PV = "1.0"
PR = "r0"

SRC_URI = "git://github.com/armbian/firmware.git;protocol=https;branch=master"
SRCREV = "3846b6c96475c9ca3bacaf49d35aad27301b9cf4"

S = "${WORKDIR}/git"

do_install() {
    install -d ${D}${base_libdir}/firmware
    install -m 0644 ${S}/uwe5622/wcnmodem.bin ${D}${base_libdir}/firmware/wcnmodem.bin
    install -m 0644 ${S}/uwe5622/wifi_2355b001_1ant.ini ${D}${base_libdir}/firmware/wifi_2355b001_1ant.ini
}

FILES:${PN} = "${base_libdir}/*"

PACKAGES = "${PN}"
