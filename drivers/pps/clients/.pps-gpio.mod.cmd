cmd_drivers/pps/clients/pps-gpio.mod := printf '%s\n'   pps-gpio.o | awk '!x[$$0]++ { print("drivers/pps/clients/"$$0) }' > drivers/pps/clients/pps-gpio.mod
