cmd_net/llc/llc.mod := printf '%s\n'   llc_core.o llc_input.o llc_output.o | awk '!x[$$0]++ { print("net/llc/"$$0) }' > net/llc/llc.mod
