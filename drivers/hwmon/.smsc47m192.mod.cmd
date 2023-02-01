cmd_drivers/hwmon/smsc47m192.mod := printf '%s\n'   smsc47m192.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/smsc47m192.mod
