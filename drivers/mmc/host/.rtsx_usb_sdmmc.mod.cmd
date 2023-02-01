cmd_drivers/mmc/host/rtsx_usb_sdmmc.mod := printf '%s\n'   rtsx_usb_sdmmc.o | awk '!x[$$0]++ { print("drivers/mmc/host/"$$0) }' > drivers/mmc/host/rtsx_usb_sdmmc.mod
