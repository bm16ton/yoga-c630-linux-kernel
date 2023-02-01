cmd_drivers/hwmon/adm1031.mod := printf '%s\n'   adm1031.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/adm1031.mod
