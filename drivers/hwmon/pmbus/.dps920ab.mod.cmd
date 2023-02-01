cmd_drivers/hwmon/pmbus/dps920ab.mod := printf '%s\n'   dps920ab.o | awk '!x[$$0]++ { print("drivers/hwmon/pmbus/"$$0) }' > drivers/hwmon/pmbus/dps920ab.mod
