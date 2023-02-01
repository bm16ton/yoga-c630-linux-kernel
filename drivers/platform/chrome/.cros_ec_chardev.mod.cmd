cmd_drivers/platform/chrome/cros_ec_chardev.mod := printf '%s\n'   cros_ec_chardev.o | awk '!x[$$0]++ { print("drivers/platform/chrome/"$$0) }' > drivers/platform/chrome/cros_ec_chardev.mod
