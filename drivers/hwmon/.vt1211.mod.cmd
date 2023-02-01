cmd_drivers/hwmon/vt1211.mod := printf '%s\n'   vt1211.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/vt1211.mod
