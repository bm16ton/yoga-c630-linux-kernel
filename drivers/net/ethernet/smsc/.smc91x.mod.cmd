cmd_drivers/net/ethernet/smsc/smc91x.mod := printf '%s\n'   smc91x.o | awk '!x[$$0]++ { print("drivers/net/ethernet/smsc/"$$0) }' > drivers/net/ethernet/smsc/smc91x.mod
