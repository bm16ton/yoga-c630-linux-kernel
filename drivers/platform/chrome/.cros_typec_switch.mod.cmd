cmd_drivers/platform/chrome/cros_typec_switch.mod := printf '%s\n'   cros_typec_switch.o | awk '!x[$$0]++ { print("drivers/platform/chrome/"$$0) }' > drivers/platform/chrome/cros_typec_switch.mod
