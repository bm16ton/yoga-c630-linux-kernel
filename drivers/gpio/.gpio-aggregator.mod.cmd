cmd_drivers/gpio/gpio-aggregator.mod := printf '%s\n'   gpio-aggregator.o | awk '!x[$$0]++ { print("drivers/gpio/"$$0) }' > drivers/gpio/gpio-aggregator.mod
