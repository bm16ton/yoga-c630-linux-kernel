cmd_drivers/gpio/gpio-tpic2810.mod := printf '%s\n'   gpio-tpic2810.o | awk '!x[$$0]++ { print("drivers/gpio/"$$0) }' > drivers/gpio/gpio-tpic2810.mod
