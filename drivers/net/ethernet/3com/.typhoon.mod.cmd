cmd_drivers/net/ethernet/3com/typhoon.mod := printf '%s\n'   typhoon.o | awk '!x[$$0]++ { print("drivers/net/ethernet/3com/"$$0) }' > drivers/net/ethernet/3com/typhoon.mod
