cmd_drivers/gpio/gpio-adnp.mod := printf '%s\n'   gpio-adnp.o | awk '!x[$$0]++ { print("drivers/gpio/"$$0) }' > drivers/gpio/gpio-adnp.mod
