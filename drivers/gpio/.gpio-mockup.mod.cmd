cmd_drivers/gpio/gpio-mockup.mod := printf '%s\n'   gpio-mockup.o | awk '!x[$$0]++ { print("drivers/gpio/"$$0) }' > drivers/gpio/gpio-mockup.mod
