cmd_drivers/hwmon/smsc47m1.mod := printf '%s\n'   smsc47m1.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/smsc47m1.mod
