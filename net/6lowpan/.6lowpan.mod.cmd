cmd_net/6lowpan/6lowpan.mod := printf '%s\n'   core.o iphc.o nhc.o ndisc.o | awk '!x[$$0]++ { print("net/6lowpan/"$$0) }' > net/6lowpan/6lowpan.mod
