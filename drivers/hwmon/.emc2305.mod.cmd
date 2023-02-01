cmd_drivers/hwmon/emc2305.mod := printf '%s\n'   emc2305.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/emc2305.mod
