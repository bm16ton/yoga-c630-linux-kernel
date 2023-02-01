cmd_drivers/firewire/firewire-net.mod := printf '%s\n'   net.o | awk '!x[$$0]++ { print("drivers/firewire/"$$0) }' > drivers/firewire/firewire-net.mod
