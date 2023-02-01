cmd_drivers/hwmon/sch5636.mod := printf '%s\n'   sch5636.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/sch5636.mod
