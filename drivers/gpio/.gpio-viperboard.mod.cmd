cmd_drivers/gpio/gpio-viperboard.mod := printf '%s\n'   gpio-viperboard.o | awk '!x[$$0]++ { print("drivers/gpio/"$$0) }' > drivers/gpio/gpio-viperboard.mod
