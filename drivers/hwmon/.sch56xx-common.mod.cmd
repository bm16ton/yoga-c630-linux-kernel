cmd_drivers/hwmon/sch56xx-common.mod := printf '%s\n'   sch56xx-common.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/sch56xx-common.mod
