cmd_drivers/hwmon/pmbus/pli1209bc.mod := printf '%s\n'   pli1209bc.o | awk '!x[$$0]++ { print("drivers/hwmon/pmbus/"$$0) }' > drivers/hwmon/pmbus/pli1209bc.mod
