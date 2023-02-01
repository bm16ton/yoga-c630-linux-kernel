cmd_drivers/hwmon/nct6775.mod := printf '%s\n'   nct6775-platform.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/nct6775.mod
