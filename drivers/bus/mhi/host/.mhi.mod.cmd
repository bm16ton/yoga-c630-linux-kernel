cmd_drivers/bus/mhi/host/mhi.mod := printf '%s\n'   init.o main.o pm.o boot.o debugfs.o | awk '!x[$$0]++ { print("drivers/bus/mhi/host/"$$0) }' > drivers/bus/mhi/host/mhi.mod
