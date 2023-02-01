cmd_drivers/rtc/rtc-mv.mod := printf '%s\n'   rtc-mv.o | awk '!x[$$0]++ { print("drivers/rtc/"$$0) }' > drivers/rtc/rtc-mv.mod
