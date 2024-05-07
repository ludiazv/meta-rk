# Boot script management
# This include implement the logic for custom envirment
SRC_URI:append = " file://boot.cmd.in file://rk35_env.txt file://exclude.txt file://spiflash.sh"

UBOOT_ENV_SUFFIX = "scr"
UBOOT_ENV = "boot"

# Custom Env and overlay management
RK35_BOOT_ENV ??= ""
RK35_BOOT_EXTRAARGS ??= ""
RK35_OVERLAYS ??= ""
RK35_INSTALL_EXTRA ??= "${@bb.utils.contains('DISTRO_FEATURES','debug-tweaks','1','0',d)}"
RK35_EXTRA_FILES = "${WORKDIR}/${UBOOT_ENV_SRC} ${B}/u-boot.itb ${B}/idbloader.img ${B}/u-boot-rockchip-spi.bin \
                    ${WORKDIR}/exclude.txt ${WORKDIR}/spiflash.sh \
                    " 



# Helper to create the custom env file and patch it if needed
rk35_uboot_env_helper() {
   local dst=$1

   local env_src="${RK35_BOOT_ENV}"
   [ ! -f "${WORKDIR}/${env_src}.txt" ] && env_src="rk35_env"
   local env_dst=${dst}/custom-${RK35_BOOT_ENV}.txt
   install -D -m 0644 ${WORKDIR}/${env_src}.txt ${env_dst}

   local ovr=${@ (d.getVar('RK35_OVERLAYS') or "").strip() }
   local extraargs=${@ (d.getVar('RK35_BOOT_EXTRAARGS') or "").strip() }
	
   #patch env file with ovelays
   if [ -n "${ovr}" ] ; then
      if grep -E -v '^#|^$' | grep 'overlays=' ; then
         sed -i "s/overlays=(.*)/overlays=\1 ${ovr}" ${env_dst}
       else
         # Simply add the overlays to the file
         echo "overlays=${ovr}" >> ${env_dst}
       fi
   fi

   #patch env file with extra args
   if [ -n "${extraargs}" ] ; then
      if grep -E -v '^#|^$' | grep 'extraargs=' ; then
         sed -i "s/extraargs=(.*)/extraargs=\1 ${extraargs}" ${env_dst}
      else
         echo "extraargs=${extraargs}" >> ${env_dst}
       fi
   fi
}

# Helper to deploy extra files related with u-boot.
# These files are not needed to boot but required to flash bootloader in the spi flash
# and perform installaction on the emmc,USB or NVME drives
rk35_uboot_extra_helper() {
   local dst=$1

   local bn=
   for f in ${RK35_EXTRA_FILES} ; do
      bn=$(basename ${f})
      [ -f ${f} ] && install -D -m 0644 ${f} ${dst}/u-boot/${bn}
   done
}

#Interpolate name of enviroment file
do_compile:prepend() {

    # First we need create the custom script before compilation.
    local rk35_local_env="${RK35_BOOT_ENV}"
    # interpolate a dummy env file to create the boot script
    [ -z "${rk35_local_env}" ] && rk35_local_env="not_used"
    sed "s,@@RK35_BOOT_ENV@@,${rk35_local_env},g" ${WORKDIR}/boot.cmd.in > ${WORKDIR}/boot.cmd

    if [ -n "${RK35_BOOT_ENV}" ] ; then
       rk35_uboot_env_helper ${B}
    fi
     
}

#Install RK35 env file if needed
do_install:append() {
   if [ -n "${RK35_BOOT_ENV}" ] ; then
      install -D -m 0644 ${B}/custom-${RK35_BOOT_ENV}.txt ${D}/boot/${RK35_BOOT_ENV}.txt
   fi
   
   if [ "${RK35_INSTALL_EXTRA}" = "1" ] ; then
      rk35_uboot_extra_helper ${D}/boot
   fi
}

#Deploy RJ35 env file if needed
do_deploy:append() {
  if [ -n "${RK35_BOOT_ENV}" ] ; then
     install -m 0644 ${B}/custom-${RK35_BOOT_ENV}.txt ${DEPLOYDIR}/${RK35_BOOT_ENV}.txt
  fi

  if [ "${RK35_INSTALL_EXTRA}" = "1" ] ; then
     rk35_uboot_extra_helper ${DEPLOYDIR}
  fi
}

# Include package boot env and extra
FILES:${PN}:append = " ${@ '/boot/' + d.getVar('RK35_BOOT_ENV') + '.txt' if (d.getVar('RK35_BOOT_ENV') or "").strip() else ''}"
FILES:${PN}:append = " ${@ '/boot/u-boot/' if d.getVar('RK35_INSTALL_EXTRA') == '1' else ''}"

# Add dependency for overlays
RDEPENDS:${PN}:append = " ${@ 'rk35-overlays' if (d.getVar('RK35_OVERLAYS') or "").strip() else ''}"



