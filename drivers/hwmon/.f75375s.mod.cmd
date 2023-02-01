cmd_drivers/hwmon/f75375s.mod := printf '%s\n'   f75375s.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/f75375s.mod
