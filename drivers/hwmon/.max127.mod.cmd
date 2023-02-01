cmd_drivers/hwmon/max127.mod := printf '%s\n'   max127.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/max127.mod
