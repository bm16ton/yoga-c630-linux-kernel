cmd_drivers/gpio/gpio-dln2.mod := printf '%s\n'   gpio-dln2.o | awk '!x[$$0]++ { print("drivers/gpio/"$$0) }' > drivers/gpio/gpio-dln2.mod
