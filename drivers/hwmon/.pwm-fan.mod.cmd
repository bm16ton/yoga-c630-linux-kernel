cmd_drivers/hwmon/pwm-fan.mod := printf '%s\n'   pwm-fan.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/pwm-fan.mod
