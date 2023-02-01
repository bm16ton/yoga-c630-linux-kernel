cmd_drivers/platform/chrome/cros_usbpd_logger.mod := printf '%s\n'   cros_usbpd_logger.o | awk '!x[$$0]++ { print("drivers/platform/chrome/"$$0) }' > drivers/platform/chrome/cros_usbpd_logger.mod
