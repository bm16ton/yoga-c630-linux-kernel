cmd_drivers/hwmon/f71805f.mod := printf '%s\n'   f71805f.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/f71805f.mod
