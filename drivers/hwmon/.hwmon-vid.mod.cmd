cmd_drivers/hwmon/hwmon-vid.mod := printf '%s\n'   hwmon-vid.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/hwmon-vid.mod
