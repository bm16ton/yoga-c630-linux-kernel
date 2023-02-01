cmd_drivers/pwm/pwm-cros-ec.mod := printf '%s\n'   pwm-cros-ec.o | awk '!x[$$0]++ { print("drivers/pwm/"$$0) }' > drivers/pwm/pwm-cros-ec.mod
