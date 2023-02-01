cmd_drivers/hwmon/pmbus/pm6764tr.mod := printf '%s\n'   pm6764tr.o | awk '!x[$$0]++ { print("drivers/hwmon/pmbus/"$$0) }' > drivers/hwmon/pmbus/pm6764tr.mod
