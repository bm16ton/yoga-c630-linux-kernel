cmd_drivers/w1/masters/w1-gpio.mod := printf '%s\n'   w1-gpio.o | awk '!x[$$0]++ { print("drivers/w1/masters/"$$0) }' > drivers/w1/masters/w1-gpio.mod
