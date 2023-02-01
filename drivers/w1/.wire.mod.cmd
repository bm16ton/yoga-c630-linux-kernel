cmd_drivers/w1/wire.mod := printf '%s\n'   w1.o w1_int.o w1_family.o w1_netlink.o w1_io.o | awk '!x[$$0]++ { print("drivers/w1/"$$0) }' > drivers/w1/wire.mod
