cmd_drivers/hwmon/adm1029.mod := printf '%s\n'   adm1029.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/adm1029.mod
