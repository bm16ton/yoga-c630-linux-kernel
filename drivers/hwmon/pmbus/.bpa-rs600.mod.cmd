cmd_drivers/hwmon/pmbus/bpa-rs600.mod := printf '%s\n'   bpa-rs600.o | awk '!x[$$0]++ { print("drivers/hwmon/pmbus/"$$0) }' > drivers/hwmon/pmbus/bpa-rs600.mod
