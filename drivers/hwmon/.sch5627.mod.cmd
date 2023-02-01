cmd_drivers/hwmon/sch5627.mod := printf '%s\n'   sch5627.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/sch5627.mod
