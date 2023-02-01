cmd_drivers/rtc/rtc-cros-ec.mod := printf '%s\n'   rtc-cros-ec.o | awk '!x[$$0]++ { print("drivers/rtc/"$$0) }' > drivers/rtc/rtc-cros-ec.mod
