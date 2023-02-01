cmd_drivers/net/ethernet/cavium/thunder/nicpf.mod := printf '%s\n'   nic_main.o | awk '!x[$$0]++ { print("drivers/net/ethernet/cavium/thunder/"$$0) }' > drivers/net/ethernet/cavium/thunder/nicpf.mod
