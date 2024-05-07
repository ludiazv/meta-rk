# meta-rk35 default settings

# kernel Provider and version
PREFERRED_PROVIDER_virtual/kernel ?= "linux-yocto"
PREFERRED_VERSION_virtual/kernel ?="6.6%"

# Use default Kernel configuration values if not defined
KCONFIG_MODE ?= "alldefconfig"

# Use defaults for kernel configuration
KBUILD_DEFCONFIG ?= "defconfig"

# Default kenerl image "Image"
KERNEL_IMAGETYPE ?= "Image"
#KERNEL_CLASSES ??= "kernel-fitimage"

# UBOOT defaults
UBOOT_SUFFIX ?= "itb"
UBOOT_ENTRYPOINT ?= "0x06000000"

# xserver
XSERVER = " \
	xserver-xorg \
	xserver-xorg-utils \
	xserver-xorg-xvfb \
	xserver-xorg-extension-glx \
	xserver-xorg-module-libwfb \
	xserver-xorg-module-exa \
	xf86-video-modesetting \
	xf86-input-evdev \
	xf86-input-mouse \
	"

# misc
SERIAL_CONSOLES ?= "1500000;ttyS2"
