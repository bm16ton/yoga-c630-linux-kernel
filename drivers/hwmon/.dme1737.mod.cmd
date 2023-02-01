cmd_drivers/hwmon/dme1737.mod := printf '%s\n'   dme1737.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/dme1737.mod
