cmd_drivers/firewire/firewire-sbp2.mod := printf '%s\n'   sbp2.o | awk '!x[$$0]++ { print("drivers/firewire/"$$0) }' > drivers/firewire/firewire-sbp2.mod
