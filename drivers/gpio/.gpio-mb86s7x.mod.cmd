cmd_drivers/gpio/gpio-mb86s7x.mod := printf '%s\n'   gpio-mb86s7x.o | awk '!x[$$0]++ { print("drivers/gpio/"$$0) }' > drivers/gpio/gpio-mb86s7x.mod
