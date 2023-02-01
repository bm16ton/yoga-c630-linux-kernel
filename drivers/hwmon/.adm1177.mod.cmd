cmd_drivers/hwmon/adm1177.mod := printf '%s\n'   adm1177.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/adm1177.mod
