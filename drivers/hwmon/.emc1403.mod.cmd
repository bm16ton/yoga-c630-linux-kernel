cmd_drivers/hwmon/emc1403.mod := printf '%s\n'   emc1403.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/emc1403.mod
