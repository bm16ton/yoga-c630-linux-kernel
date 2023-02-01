cmd_drivers/gpio/gpio-xra1403.mod := printf '%s\n'   gpio-xra1403.o | awk '!x[$$0]++ { print("drivers/gpio/"$$0) }' > drivers/gpio/gpio-xra1403.mod
