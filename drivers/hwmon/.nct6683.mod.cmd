cmd_drivers/hwmon/nct6683.mod := printf '%s\n'   nct6683.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/nct6683.mod
