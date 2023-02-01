cmd_drivers/hwmon/nct6775-i2c.mod := printf '%s\n'   nct6775-i2c.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/nct6775-i2c.mod
