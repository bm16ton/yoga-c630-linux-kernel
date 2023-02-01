cmd_drivers/gpio/gpio-pca9570.mod := printf '%s\n'   gpio-pca9570.o | awk '!x[$$0]++ { print("drivers/gpio/"$$0) }' > drivers/gpio/gpio-pca9570.mod
