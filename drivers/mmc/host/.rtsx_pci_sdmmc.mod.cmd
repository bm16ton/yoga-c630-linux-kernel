cmd_drivers/mmc/host/rtsx_pci_sdmmc.mod := printf '%s\n'   rtsx_pci_sdmmc.o | awk '!x[$$0]++ { print("drivers/mmc/host/"$$0) }' > drivers/mmc/host/rtsx_pci_sdmmc.mod
