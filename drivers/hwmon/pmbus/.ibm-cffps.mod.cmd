cmd_drivers/hwmon/pmbus/ibm-cffps.mod := printf '%s\n'   ibm-cffps.o | awk '!x[$$0]++ { print("drivers/hwmon/pmbus/"$$0) }' > drivers/hwmon/pmbus/ibm-cffps.mod
