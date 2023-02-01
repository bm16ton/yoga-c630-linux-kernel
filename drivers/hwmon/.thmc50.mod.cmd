cmd_drivers/hwmon/thmc50.mod := printf '%s\n'   thmc50.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/thmc50.mod
