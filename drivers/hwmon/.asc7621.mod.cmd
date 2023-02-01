cmd_drivers/hwmon/asc7621.mod := printf '%s\n'   asc7621.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/asc7621.mod
