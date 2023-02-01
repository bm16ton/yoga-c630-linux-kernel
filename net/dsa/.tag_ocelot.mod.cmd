cmd_net/dsa/tag_ocelot.mod := printf '%s\n'   tag_ocelot.o | awk '!x[$$0]++ { print("net/dsa/"$$0) }' > net/dsa/tag_ocelot.mod
