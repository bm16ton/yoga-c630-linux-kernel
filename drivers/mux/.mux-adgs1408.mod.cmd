cmd_drivers/mux/mux-adgs1408.mod := printf '%s\n'   adgs1408.o | awk '!x[$$0]++ { print("drivers/mux/"$$0) }' > drivers/mux/mux-adgs1408.mod
