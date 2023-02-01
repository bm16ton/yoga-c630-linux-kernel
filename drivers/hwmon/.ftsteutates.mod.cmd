cmd_drivers/hwmon/ftsteutates.mod := printf '%s\n'   ftsteutates.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/ftsteutates.mod
