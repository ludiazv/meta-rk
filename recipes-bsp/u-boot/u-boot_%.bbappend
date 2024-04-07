# various machines require the pyelftools library for parsing dtb files
FILESEXTRAPATHS:prepend := "${THISDIR}/files:"
DEPENDS:append = " python3-pyelftools-native"

EXTRA_OEMAKE:append:rk3588s = " \
	BL31=${DEPLOY_DIR_IMAGE}/bl31-rk3588.elf \
	ROCKCHIP_TPL=${DEPLOY_DIR_IMAGE}/ddr-rk3588.bin \
	"

EXTRA_OEMAKE:append:rk3566 = " \
	BL31=${DEPLOY_DIR_IMAGE}/bl31-rk3566.elf \
	ROCKCHIP_TPL=${DEPLOY_DIR_IMAGE}/ddr-rk3566.bin \
	"

INIT_FIRMWARE_DEPENDS ??= ""
INIT_FIRMWARE_DEPENDS:rk3588s = " rockchip-rkbin:do_deploy"
INIT_FIRMWARE_DEPENDS:rk3566 = " rockchip-rkbin:do_deploy"


		

SRC_URI:orangepi-3b = "git://github.com/Kwiboo/u-boot-rockchip.git;protocol=https;branch=rk3568-2023.10"
SRCREV:orangepi-3b = "0bc339ffa6f804d51c5c5292d8ff69c4d79614d3"
#SRC_URI:orangepi-3b = " git://github.com/Kwiboo/u-boot-rockchip.git;protocol=https;branch=rk35xx-2024.01"
#SRCREV:orangepi-3b = "583d37d192d92c5e92efa68b1d97f8ecdef71c47"


do_compile[depends] .= "${INIT_FIRMWARE_DEPENDS}"

# custom-env
require recipes-bsp/u-boot/custom-env.inc
