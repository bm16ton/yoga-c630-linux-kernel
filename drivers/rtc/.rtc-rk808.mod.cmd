cmd_drivers/rtc/rtc-rk808.mod := printf '%s\n'   rtc-rk808.o | awk '!x[$$0]++ { print("drivers/rtc/"$$0) }' > drivers/rtc/rtc-rk808.mod
