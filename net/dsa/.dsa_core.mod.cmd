cmd_net/dsa/dsa_core.mod := printf '%s\n'   dsa.o dsa2.o master.o netlink.o port.o slave.o switch.o tag_8021q.o | awk '!x[$$0]++ { print("net/dsa/"$$0) }' > net/dsa/dsa_core.mod
