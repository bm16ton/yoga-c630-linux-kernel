cmd_drivers/mfd/cros_ec_dev.mod := printf '%s\n'   cros_ec_dev.o | awk '!x[$$0]++ { print("drivers/mfd/"$$0) }' > drivers/mfd/cros_ec_dev.mod
