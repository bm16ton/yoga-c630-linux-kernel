cmd_drivers/hwmon/ina2xx.mod := printf '%s\n'   ina2xx.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/ina2xx.mod
