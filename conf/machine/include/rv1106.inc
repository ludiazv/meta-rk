MACHINEOVERRIDES =. "rv1106:"
#DEFAULTTUNE ?= "cortexa7hf-neon-vfpv4"

require conf/machine/include/arm/armv7a/tune-cortexa7.inc

# Use specific u-boot provided by pico sdk
PREFERRED_PROVIDER_u-boot="u-boot-pico"
PREFERRED_PROVIDER_virtual/bootloader="u-boot-pico"
# Use specific kernel provided by pico sdk
#PREFERRED_PROVIDER_linux="linux-pico"
PREFERRED_PROVIDER_virtual/kernel="linux-pico"

#UBOOT - set .img the extension of the u-boot binary
UBOOT_SUFFIX = "img"

# WKS - Custom wks with mrb partion
IMAGE_FSTYPES += "wic.gz wic.bmap"
WKS_FILE = "rockchip-rv11xx.wks"
WKS_FILE_DEPENDS ?= " \
	mtools-native \
	dosfstools-native \
	e2fsprogs-native \
	virtual/bootloader \
	virtual/kernel \
	"

# Defaults to zImage
KERNEL_IMAGETYPE ?= "zImage"

# Files in the boot partition kernel + dt.dtb
IMAGE_BOOT_FILES += " \
	${KERNEL_IMAGETYPE}  \
        ${KERNEL_DEVICETREE};dt.dtb \
"


# Set serial consoles
SERIAL_CONSOLES ?= "115200;ttyFIQ0"

#Disable tty1 as the chip does not have video
SYSVINIT_ENABLED_GETTYS := ""

