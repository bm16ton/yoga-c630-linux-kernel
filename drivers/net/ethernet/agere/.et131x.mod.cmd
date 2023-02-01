cmd_drivers/net/ethernet/agere/et131x.mod := printf '%s\n'   et131x.o | awk '!x[$$0]++ { print("drivers/net/ethernet/agere/"$$0) }' > drivers/net/ethernet/agere/et131x.mod
