cmd_drivers/net/ethernet/dec/tulip/winbond-840.mod := printf '%s\n'   winbond-840.o | awk '!x[$$0]++ { print("drivers/net/ethernet/dec/tulip/"$$0) }' > drivers/net/ethernet/dec/tulip/winbond-840.mod
