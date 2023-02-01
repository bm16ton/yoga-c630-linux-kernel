cmd_drivers/hwmon/vexpress-hwmon.mod := printf '%s\n'   vexpress-hwmon.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/vexpress-hwmon.mod
