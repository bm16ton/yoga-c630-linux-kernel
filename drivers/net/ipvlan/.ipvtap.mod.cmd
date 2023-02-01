cmd_drivers/net/ipvlan/ipvtap.mod := printf '%s\n'   ipvtap.o | awk '!x[$$0]++ { print("drivers/net/ipvlan/"$$0) }' > drivers/net/ipvlan/ipvtap.mod
