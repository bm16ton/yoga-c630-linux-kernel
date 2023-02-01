cmd_drivers/hwmon/f71882fg.mod := printf '%s\n'   f71882fg.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/f71882fg.mod
