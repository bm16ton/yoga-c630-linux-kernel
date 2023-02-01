cmd_drivers/firewire/firewire-ohci.mod := printf '%s\n'   ohci.o | awk '!x[$$0]++ { print("drivers/firewire/"$$0) }' > drivers/firewire/firewire-ohci.mod
