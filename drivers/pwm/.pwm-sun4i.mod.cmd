cmd_drivers/pwm/pwm-sun4i.mod := printf '%s\n'   pwm-sun4i.o | awk '!x[$$0]++ { print("drivers/pwm/"$$0) }' > drivers/pwm/pwm-sun4i.mod
