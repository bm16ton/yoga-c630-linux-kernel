cmd_drivers/hwmon/w83781d.mod := printf '%s\n'   w83781d.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/w83781d.mod
