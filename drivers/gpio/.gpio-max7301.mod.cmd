cmd_drivers/gpio/gpio-max7301.mod := printf '%s\n'   gpio-max7301.o | awk '!x[$$0]++ { print("drivers/gpio/"$$0) }' > drivers/gpio/gpio-max7301.mod
