cmd_drivers/gpio/gpio-sim.mod := printf '%s\n'   gpio-sim.o | awk '!x[$$0]++ { print("drivers/gpio/"$$0) }' > drivers/gpio/gpio-sim.mod
