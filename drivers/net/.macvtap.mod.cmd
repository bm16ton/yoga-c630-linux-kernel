cmd_drivers/net/macvtap.mod := printf '%s\n'   macvtap.o | awk '!x[$$0]++ { print("drivers/net/"$$0) }' > drivers/net/macvtap.mod
