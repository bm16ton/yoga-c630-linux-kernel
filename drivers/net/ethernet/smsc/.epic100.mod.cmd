cmd_drivers/net/ethernet/smsc/epic100.mod := printf '%s\n'   epic100.o | awk '!x[$$0]++ { print("drivers/net/ethernet/smsc/"$$0) }' > drivers/net/ethernet/smsc/epic100.mod
