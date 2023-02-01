cmd_drivers/w1/slaves/w1_therm.mod := printf '%s\n'   w1_therm.o | awk '!x[$$0]++ { print("drivers/w1/slaves/"$$0) }' > drivers/w1/slaves/w1_therm.mod
