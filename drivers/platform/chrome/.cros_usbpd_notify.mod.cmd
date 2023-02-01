cmd_drivers/platform/chrome/cros_usbpd_notify.mod := printf '%s\n'   cros_usbpd_notify.o | awk '!x[$$0]++ { print("drivers/platform/chrome/"$$0) }' > drivers/platform/chrome/cros_usbpd_notify.mod
