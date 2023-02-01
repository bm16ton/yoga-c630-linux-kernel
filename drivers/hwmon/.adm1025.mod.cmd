cmd_drivers/hwmon/adm1025.mod := printf '%s\n'   adm1025.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/adm1025.mod
