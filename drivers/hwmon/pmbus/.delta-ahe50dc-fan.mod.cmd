cmd_drivers/hwmon/pmbus/delta-ahe50dc-fan.mod := printf '%s\n'   delta-ahe50dc-fan.o | awk '!x[$$0]++ { print("drivers/hwmon/pmbus/"$$0) }' > drivers/hwmon/pmbus/delta-ahe50dc-fan.mod
