cmd_net/rfkill/rfkill.mod := printf '%s\n'   core.o input.o | awk '!x[$$0]++ { print("net/rfkill/"$$0) }' > net/rfkill/rfkill.mod
