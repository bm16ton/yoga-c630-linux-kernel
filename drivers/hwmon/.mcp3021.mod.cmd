cmd_drivers/hwmon/mcp3021.mod := printf '%s\n'   mcp3021.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/mcp3021.mod
