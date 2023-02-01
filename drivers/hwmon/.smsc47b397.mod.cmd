cmd_drivers/hwmon/smsc47b397.mod := printf '%s\n'   smsc47b397.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/smsc47b397.mod
