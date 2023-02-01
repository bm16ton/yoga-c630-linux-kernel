cmd_drivers/hwmon/w83773g.mod := printf '%s\n'   w83773g.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/w83773g.mod
