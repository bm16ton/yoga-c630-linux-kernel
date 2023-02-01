cmd_drivers/net/ethernet/qlogic/qla3xxx.mod := printf '%s\n'   qla3xxx.o | awk '!x[$$0]++ { print("drivers/net/ethernet/qlogic/"$$0) }' > drivers/net/ethernet/qlogic/qla3xxx.mod
