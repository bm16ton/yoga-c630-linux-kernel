cmd_drivers/net/wireless/ralink/rt2x00/rt61pci.mod := printf '%s\n'   rt61pci.o | awk '!x[$$0]++ { print("drivers/net/wireless/ralink/rt2x00/"$$0) }' > drivers/net/wireless/ralink/rt2x00/rt61pci.mod
