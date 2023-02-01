cmd_drivers/hwmon/xgene-hwmon.mod := printf '%s\n'   xgene-hwmon.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/xgene-hwmon.mod
