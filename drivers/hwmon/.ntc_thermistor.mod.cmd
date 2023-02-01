cmd_drivers/hwmon/ntc_thermistor.mod := printf '%s\n'   ntc_thermistor.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/ntc_thermistor.mod
