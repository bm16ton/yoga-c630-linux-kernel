cmd_drivers/hwmon/g760a.mod := printf '%s\n'   g760a.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/g760a.mod
