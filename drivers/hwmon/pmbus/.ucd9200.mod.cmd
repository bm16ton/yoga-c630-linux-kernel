cmd_drivers/hwmon/pmbus/ucd9200.mod := printf '%s\n'   ucd9200.o | awk '!x[$$0]++ { print("drivers/hwmon/pmbus/"$$0) }' > drivers/hwmon/pmbus/ucd9200.mod
