cmd_drivers/hwmon/pmbus/lm25066.mod := printf '%s\n'   lm25066.o | awk '!x[$$0]++ { print("drivers/hwmon/pmbus/"$$0) }' > drivers/hwmon/pmbus/lm25066.mod
