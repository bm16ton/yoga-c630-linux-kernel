cmd_drivers/hwmon/tmp464.mod := printf '%s\n'   tmp464.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/tmp464.mod
