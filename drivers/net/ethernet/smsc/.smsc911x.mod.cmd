cmd_drivers/net/ethernet/smsc/smsc911x.mod := printf '%s\n'   smsc911x.o | awk '!x[$$0]++ { print("drivers/net/ethernet/smsc/"$$0) }' > drivers/net/ethernet/smsc/smsc911x.mod
