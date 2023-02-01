cmd_drivers/hwmon/adm1026.mod := printf '%s\n'   adm1026.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/adm1026.mod
