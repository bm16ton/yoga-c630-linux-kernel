cmd_drivers/gpio/gpio-pcie-idio-24.mod := printf '%s\n'   gpio-pcie-idio-24.o | awk '!x[$$0]++ { print("drivers/gpio/"$$0) }' > drivers/gpio/gpio-pcie-idio-24.mod
