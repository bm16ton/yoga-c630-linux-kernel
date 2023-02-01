cmd_drivers/gpio/gpio-wcd934x.mod := printf '%s\n'   gpio-wcd934x.o | awk '!x[$$0]++ { print("drivers/gpio/"$$0) }' > drivers/gpio/gpio-wcd934x.mod
