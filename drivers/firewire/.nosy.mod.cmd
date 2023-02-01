cmd_drivers/firewire/nosy.mod := printf '%s\n'   nosy.o | awk '!x[$$0]++ { print("drivers/firewire/"$$0) }' > drivers/firewire/nosy.mod
