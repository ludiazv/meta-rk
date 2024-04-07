DESCRIPTION = "Support for deploy DT overlays"
LICENSE = "MIT"

inherit devicetree

SRC_URI:rk3566:append = " file://rk3566-sata.dts"

COMPATIBLE_MACHINE = "rk3566"
