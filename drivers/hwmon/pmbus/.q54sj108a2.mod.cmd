cmd_drivers/hwmon/pmbus/q54sj108a2.mod := printf '%s\n'   q54sj108a2.o | awk '!x[$$0]++ { print("drivers/hwmon/pmbus/"$$0) }' > drivers/hwmon/pmbus/q54sj108a2.mod
