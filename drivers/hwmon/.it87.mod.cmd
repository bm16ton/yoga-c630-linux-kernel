cmd_drivers/hwmon/it87.mod := printf '%s\n'   it87.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/it87.mod
