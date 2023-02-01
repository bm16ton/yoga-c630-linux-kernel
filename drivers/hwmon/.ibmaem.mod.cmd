cmd_drivers/hwmon/ibmaem.mod := printf '%s\n'   ibmaem.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/ibmaem.mod
