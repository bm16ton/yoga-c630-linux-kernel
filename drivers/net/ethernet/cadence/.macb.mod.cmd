cmd_drivers/net/ethernet/cadence/macb.mod := printf '%s\n'   macb_main.o macb_ptp.o | awk '!x[$$0]++ { print("drivers/net/ethernet/cadence/"$$0) }' > drivers/net/ethernet/cadence/macb.mod
