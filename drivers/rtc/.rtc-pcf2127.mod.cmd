cmd_drivers/rtc/rtc-pcf2127.mod := printf '%s\n'   rtc-pcf2127.o | awk '!x[$$0]++ { print("drivers/rtc/"$$0) }' > drivers/rtc/rtc-pcf2127.mod
