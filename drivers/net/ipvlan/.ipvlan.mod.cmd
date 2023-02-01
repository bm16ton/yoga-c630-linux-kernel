cmd_drivers/net/ipvlan/ipvlan.mod := printf '%s\n'   ipvlan_core.o ipvlan_main.o ipvlan_l3s.o | awk '!x[$$0]++ { print("drivers/net/ipvlan/"$$0) }' > drivers/net/ipvlan/ipvlan.mod
