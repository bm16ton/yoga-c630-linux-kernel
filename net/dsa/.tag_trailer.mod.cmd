cmd_net/dsa/tag_trailer.mod := printf '%s\n'   tag_trailer.o | awk '!x[$$0]++ { print("net/dsa/"$$0) }' > net/dsa/tag_trailer.mod
