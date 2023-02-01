cmd_drivers/gpio/gpio-zynq.mod := printf '%s\n'   gpio-zynq.o | awk '!x[$$0]++ { print("drivers/gpio/"$$0) }' > drivers/gpio/gpio-zynq.mod
