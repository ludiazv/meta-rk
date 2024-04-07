FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}:"

# if custom enviroment is enabled featture is enable devicetrees need to be compiled with symbols
KERNEL_DTC_FLAGS += " ${@ '-@ -H epapr' if (d.getVar('RK35_BOOT_ENV') or '').strip() else ''}"

# Compatible machine
COMPATIBLE_MACHINE:orangepi-3b = "orangepi-3b"

# kmeta append
SRC_URI:append = " file://rockchip-kmeta;type=kmeta;name=rockchip-kmeta;destsuffix=rockchip-kmeta"


