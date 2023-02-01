cmd_drivers/hwmon/pmbus/inspur-ipsps.mod := printf '%s\n'   inspur-ipsps.o | awk '!x[$$0]++ { print("drivers/hwmon/pmbus/"$$0) }' > drivers/hwmon/pmbus/inspur-ipsps.mod
