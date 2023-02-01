cmd_drivers/hwmon/gpio-fan.mod := printf '%s\n'   gpio-fan.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/gpio-fan.mod
