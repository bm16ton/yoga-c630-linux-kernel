cmd_drivers/hwmon/via686a.mod := printf '%s\n'   via686a.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/via686a.mod
