cmd_net/dsa/tag_dsa.mod := printf '%s\n'   tag_dsa.o | awk '!x[$$0]++ { print("net/dsa/"$$0) }' > net/dsa/tag_dsa.mod
