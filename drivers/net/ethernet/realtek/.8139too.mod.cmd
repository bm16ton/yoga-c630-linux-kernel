cmd_drivers/net/ethernet/realtek/8139too.mod := printf '%s\n'   8139too.o | awk '!x[$$0]++ { print("drivers/net/ethernet/realtek/"$$0) }' > drivers/net/ethernet/realtek/8139too.mod
