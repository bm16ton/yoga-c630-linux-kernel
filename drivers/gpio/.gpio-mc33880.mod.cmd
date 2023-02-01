cmd_drivers/gpio/gpio-mc33880.mod := printf '%s\n'   gpio-mc33880.o | awk '!x[$$0]++ { print("drivers/gpio/"$$0) }' > drivers/gpio/gpio-mc33880.mod
