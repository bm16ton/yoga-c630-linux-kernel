cmd_drivers/gpio/gpio-max730x.mod := printf '%s\n'   gpio-max730x.o | awk '!x[$$0]++ { print("drivers/gpio/"$$0) }' > drivers/gpio/gpio-max730x.mod
