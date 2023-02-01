cmd_net/mac802154/mac802154.mod := printf '%s\n'   main.o rx.o tx.o mac_cmd.o mib.o iface.o llsec.o util.o cfg.o trace.o | awk '!x[$$0]++ { print("net/mac802154/"$$0) }' > net/mac802154/mac802154.mod
