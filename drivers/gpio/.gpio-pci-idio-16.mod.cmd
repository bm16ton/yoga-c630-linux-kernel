cmd_drivers/gpio/gpio-pci-idio-16.mod := printf '%s\n'   gpio-pci-idio-16.o | awk '!x[$$0]++ { print("drivers/gpio/"$$0) }' > drivers/gpio/gpio-pci-idio-16.mod
