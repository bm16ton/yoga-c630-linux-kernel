cmd_drivers/hwmon/adm9240.mod := printf '%s\n'   adm9240.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/adm9240.mod
