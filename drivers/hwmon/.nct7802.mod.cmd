cmd_drivers/hwmon/nct7802.mod := printf '%s\n'   nct7802.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/nct7802.mod
