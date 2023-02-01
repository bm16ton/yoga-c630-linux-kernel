cmd_drivers/gpio/gpio-max732x.mod := printf '%s\n'   gpio-max732x.o | awk '!x[$$0]++ { print("drivers/gpio/"$$0) }' > drivers/gpio/gpio-max732x.mod
