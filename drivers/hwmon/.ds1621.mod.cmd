cmd_drivers/hwmon/ds1621.mod := printf '%s\n'   ds1621.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/ds1621.mod
