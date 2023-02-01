cmd_drivers/gpio/gpio-gw-pld.mod := printf '%s\n'   gpio-gw-pld.o | awk '!x[$$0]++ { print("drivers/gpio/"$$0) }' > drivers/gpio/gpio-gw-pld.mod
