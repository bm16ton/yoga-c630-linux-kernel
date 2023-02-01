cmd_drivers/hwmon/emc6w201.mod := printf '%s\n'   emc6w201.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/emc6w201.mod
