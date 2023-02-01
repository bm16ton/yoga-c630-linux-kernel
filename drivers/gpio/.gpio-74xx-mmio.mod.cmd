cmd_drivers/gpio/gpio-74xx-mmio.mod := printf '%s\n'   gpio-74xx-mmio.o | awk '!x[$$0]++ { print("drivers/gpio/"$$0) }' > drivers/gpio/gpio-74xx-mmio.mod
