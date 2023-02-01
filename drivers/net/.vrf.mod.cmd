cmd_drivers/net/vrf.mod := printf '%s\n'   vrf.o | awk '!x[$$0]++ { print("drivers/net/"$$0) }' > drivers/net/vrf.mod
