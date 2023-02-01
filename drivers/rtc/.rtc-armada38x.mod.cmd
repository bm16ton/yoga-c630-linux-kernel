cmd_drivers/rtc/rtc-armada38x.mod := printf '%s\n'   rtc-armada38x.o | awk '!x[$$0]++ { print("drivers/rtc/"$$0) }' > drivers/rtc/rtc-armada38x.mod
