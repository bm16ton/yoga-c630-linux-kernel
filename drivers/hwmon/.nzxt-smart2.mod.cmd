cmd_drivers/hwmon/nzxt-smart2.mod := printf '%s\n'   nzxt-smart2.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/nzxt-smart2.mod
