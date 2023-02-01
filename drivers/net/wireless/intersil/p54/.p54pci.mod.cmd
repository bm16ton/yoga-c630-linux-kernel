cmd_drivers/net/wireless/intersil/p54/p54pci.mod := printf '%s\n'   p54pci.o | awk '!x[$$0]++ { print("drivers/net/wireless/intersil/p54/"$$0) }' > drivers/net/wireless/intersil/p54/p54pci.mod
