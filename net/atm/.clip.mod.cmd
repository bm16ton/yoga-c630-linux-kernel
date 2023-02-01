cmd_net/atm/clip.mod := printf '%s\n'   clip.o | awk '!x[$$0]++ { print("net/atm/"$$0) }' > net/atm/clip.mod
