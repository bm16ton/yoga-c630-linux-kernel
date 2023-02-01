cmd_drivers/hwmon/adcxx.mod := printf '%s\n'   adcxx.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/adcxx.mod
