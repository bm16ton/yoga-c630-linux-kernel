cmd_drivers/bus/mhi/ep/mhi_ep.mod := printf '%s\n'   main.o mmio.o ring.o sm.o | awk '!x[$$0]++ { print("drivers/bus/mhi/ep/"$$0) }' > drivers/bus/mhi/ep/mhi_ep.mod
