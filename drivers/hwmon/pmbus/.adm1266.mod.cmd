cmd_drivers/hwmon/pmbus/adm1266.mod := printf '%s\n'   adm1266.o | awk '!x[$$0]++ { print("drivers/hwmon/pmbus/"$$0) }' > drivers/hwmon/pmbus/adm1266.mod
