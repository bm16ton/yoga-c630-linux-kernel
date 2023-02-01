cmd_drivers/hwmon/atxp1.mod := printf '%s\n'   atxp1.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/atxp1.mod
