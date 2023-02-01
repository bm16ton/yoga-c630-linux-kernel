cmd_drivers/hwmon/max16065.mod := printf '%s\n'   max16065.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/max16065.mod
