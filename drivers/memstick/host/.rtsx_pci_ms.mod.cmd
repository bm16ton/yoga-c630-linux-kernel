cmd_drivers/memstick/host/rtsx_pci_ms.mod := printf '%s\n'   rtsx_pci_ms.o | awk '!x[$$0]++ { print("drivers/memstick/host/"$$0) }' > drivers/memstick/host/rtsx_pci_ms.mod
