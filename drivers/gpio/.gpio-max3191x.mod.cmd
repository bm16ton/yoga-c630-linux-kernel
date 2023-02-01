cmd_drivers/gpio/gpio-max3191x.mod := printf '%s\n'   gpio-max3191x.o | awk '!x[$$0]++ { print("drivers/gpio/"$$0) }' > drivers/gpio/gpio-max3191x.mod
