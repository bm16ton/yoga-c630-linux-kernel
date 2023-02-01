cmd_net/dsa/tag_ocelot_8021q.mod := printf '%s\n'   tag_ocelot_8021q.o | awk '!x[$$0]++ { print("net/dsa/"$$0) }' > net/dsa/tag_ocelot_8021q.mod
