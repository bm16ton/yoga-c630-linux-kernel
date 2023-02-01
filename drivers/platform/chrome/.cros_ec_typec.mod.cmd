cmd_drivers/platform/chrome/cros_ec_typec.mod := printf '%s\n'   cros_ec_typec.o | awk '!x[$$0]++ { print("drivers/platform/chrome/"$$0) }' > drivers/platform/chrome/cros_ec_typec.mod
