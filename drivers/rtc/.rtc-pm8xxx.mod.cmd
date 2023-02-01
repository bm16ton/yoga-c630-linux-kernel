cmd_drivers/rtc/rtc-pm8xxx.mod := printf '%s\n'   rtc-pm8xxx.o | awk '!x[$$0]++ { print("drivers/rtc/"$$0) }' > drivers/rtc/rtc-pm8xxx.mod
