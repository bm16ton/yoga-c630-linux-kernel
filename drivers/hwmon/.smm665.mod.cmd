cmd_drivers/hwmon/smm665.mod := printf '%s\n'   smm665.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/smm665.mod
