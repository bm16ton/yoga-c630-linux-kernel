cmd_drivers/hwmon/powr1220.mod := printf '%s\n'   powr1220.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/powr1220.mod
