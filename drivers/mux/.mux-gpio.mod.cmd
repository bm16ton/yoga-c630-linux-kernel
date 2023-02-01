cmd_drivers/mux/mux-gpio.mod := printf '%s\n'   gpio.o | awk '!x[$$0]++ { print("drivers/mux/"$$0) }' > drivers/mux/mux-gpio.mod
