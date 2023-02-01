cmd_drivers/hwmon/stts751.mod := printf '%s\n'   stts751.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/stts751.mod
