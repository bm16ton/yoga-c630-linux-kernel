cmd_drivers/gpio/gpio-pisosr.mod := printf '%s\n'   gpio-pisosr.o | awk '!x[$$0]++ { print("drivers/gpio/"$$0) }' > drivers/gpio/gpio-pisosr.mod
