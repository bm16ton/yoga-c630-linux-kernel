cmd_drivers/gpio/gpio-pcf857x.mod := printf '%s\n'   gpio-pcf857x.o | awk '!x[$$0]++ { print("drivers/gpio/"$$0) }' > drivers/gpio/gpio-pcf857x.mod
