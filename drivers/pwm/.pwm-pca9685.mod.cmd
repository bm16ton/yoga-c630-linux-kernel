cmd_drivers/pwm/pwm-pca9685.mod := printf '%s\n'   pwm-pca9685.o | awk '!x[$$0]++ { print("drivers/pwm/"$$0) }' > drivers/pwm/pwm-pca9685.mod
