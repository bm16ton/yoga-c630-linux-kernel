cmd_drivers/rtc/rtc-rv8803.mod := printf '%s\n'   rtc-rv8803.o | awk '!x[$$0]++ { print("drivers/rtc/"$$0) }' > drivers/rtc/rtc-rv8803.mod
