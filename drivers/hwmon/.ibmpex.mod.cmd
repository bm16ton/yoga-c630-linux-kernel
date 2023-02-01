cmd_drivers/hwmon/ibmpex.mod := printf '%s\n'   ibmpex.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/ibmpex.mod
