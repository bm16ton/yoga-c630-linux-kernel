cmd_drivers/hwmon/emc2103.mod := printf '%s\n'   emc2103.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/emc2103.mod
