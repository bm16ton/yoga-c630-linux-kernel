cmd_drivers/gpio/gpio-exar.mod := printf '%s\n'   gpio-exar.o | awk '!x[$$0]++ { print("drivers/gpio/"$$0) }' > drivers/gpio/gpio-exar.mod
