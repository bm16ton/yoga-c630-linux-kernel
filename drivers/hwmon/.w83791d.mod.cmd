cmd_drivers/hwmon/w83791d.mod := printf '%s\n'   w83791d.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/w83791d.mod
