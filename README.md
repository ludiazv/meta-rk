# Custom layers for some rockchips SBCs


A non official yocto layer for some rockchips. This is a work in progress
project intended to create basic bootable linux from a SD card.


## Usage:

As in other bsp layers addd to your ```local.conf```:

```bash
MACHINE="<supported board name>"
```

### Boot enviroment and DT overaly support

By the default the layer does not support passing specific kernel parameters from
from the bootloader. To activate this feature activate the following variables:

To deploy a custon boot enviroment add the folllowint to ```local.conf```:


```bash
RK35_BOOT_ENV="<name of the boot enviroment file (without .txt)>"
# Optinaly you can also add extra kernel arguments using
# RK35_BOOT_EXTRAARGS="<your kernel parameters>"
```

To add device tree overlays two steps are required:

1. Add a custom bbappend for the recepie ```recipies-kernel/rk35-overlays```` as follow:
```bash
FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

# Multiple dts files can be appened
SRC_URI:append = " file://<your overlay>.dts"

```

2. Add the overlay to your configuration file in the following variable:

```bash
RK35_OVERLAYS = " <your overlay names separed by spaces (without .dts)>"
```

## Supported boards

- Orange Pi 3B with support for Ethenet, USB, EMMC, NVME, Wifi. 
- Luckfox pico Mini A without overlay support.


## ToDo

- Orange Pi CM4
- Other variants fo Luckfox





