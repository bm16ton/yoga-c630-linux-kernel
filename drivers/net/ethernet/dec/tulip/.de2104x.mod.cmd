cmd_drivers/net/ethernet/dec/tulip/de2104x.mod := printf '%s\n'   de2104x.o | awk '!x[$$0]++ { print("drivers/net/ethernet/dec/tulip/"$$0) }' > drivers/net/ethernet/dec/tulip/de2104x.mod
