cmd_drivers/mux/mux-core.mod := printf '%s\n'   core.o | awk '!x[$$0]++ { print("drivers/mux/"$$0) }' > drivers/mux/mux-core.mod
