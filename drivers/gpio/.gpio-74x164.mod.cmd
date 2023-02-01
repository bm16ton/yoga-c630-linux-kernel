cmd_drivers/gpio/gpio-74x164.mod := printf '%s\n'   gpio-74x164.o | awk '!x[$$0]++ { print("drivers/gpio/"$$0) }' > drivers/gpio/gpio-74x164.mod
