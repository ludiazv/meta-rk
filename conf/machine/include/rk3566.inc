MACHINEOVERRIDES =. "rk3566:"
DEFAULTTUNE ?= "cortexa55"

require conf/machine/include/arm/armv8-2a/tune-cortexa55.inc
require conf/machine/include/rockchip-defaults.inc
require conf/machine/include/rockchip-wic.inc

KERNEL_FEATURES:append:rk3566 = " bsp/rockchip/remove-non-rockchip-arch-arm64.scc"

PREFERRED_PROVIDER_trusted-firmware-a = "rockchip-rkbin"
PREFERRED_PROVIDER_optee-os = "rockchip-rkbin"

# Add initramfs if needed
INITRAMFS_IMAGE ?= "${@ 'rk35-initramfs' if d.getVar('RK35_INITRAMFS') == "1" else '' }"
INITRAMFS_FSTYPES ?= "${@ 'cpio.gz.u-boot' if d.getVar('RK35_INITRAMFS') == "1" else ''}" 
# vim:set ft=bitbake:
