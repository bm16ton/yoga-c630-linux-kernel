cmd_drivers/net/mhi_net.mod := printf '%s\n'   mhi_net.o | awk '!x[$$0]++ { print("drivers/net/"$$0) }' > drivers/net/mhi_net.mod
