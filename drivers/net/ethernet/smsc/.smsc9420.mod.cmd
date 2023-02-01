cmd_drivers/net/ethernet/smsc/smsc9420.mod := printf '%s\n'   smsc9420.o | awk '!x[$$0]++ { print("drivers/net/ethernet/smsc/"$$0) }' > drivers/net/ethernet/smsc/smsc9420.mod
