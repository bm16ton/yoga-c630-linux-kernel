cmd_drivers/hwmon/pmbus/adm1275.mod := printf '%s\n'   adm1275.o | awk '!x[$$0]++ { print("drivers/hwmon/pmbus/"$$0) }' > drivers/hwmon/pmbus/adm1275.mod
