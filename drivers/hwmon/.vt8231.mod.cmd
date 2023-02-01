cmd_drivers/hwmon/vt8231.mod := printf '%s\n'   vt8231.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/vt8231.mod
