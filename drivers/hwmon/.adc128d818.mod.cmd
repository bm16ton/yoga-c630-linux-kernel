cmd_drivers/hwmon/adc128d818.mod := printf '%s\n'   adc128d818.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/adc128d818.mod
