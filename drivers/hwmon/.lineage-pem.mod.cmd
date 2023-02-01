cmd_drivers/hwmon/lineage-pem.mod := printf '%s\n'   lineage-pem.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/lineage-pem.mod
