cmd_drivers/net/ethernet/alteon/acenic.mod := printf '%s\n'   acenic.o | awk '!x[$$0]++ { print("drivers/net/ethernet/alteon/"$$0) }' > drivers/net/ethernet/alteon/acenic.mod
