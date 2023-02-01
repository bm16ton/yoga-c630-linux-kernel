cmd_drivers/hwmon/pmbus/bel-pfe.mod := printf '%s\n'   bel-pfe.o | awk '!x[$$0]++ { print("drivers/hwmon/pmbus/"$$0) }' > drivers/hwmon/pmbus/bel-pfe.mod
