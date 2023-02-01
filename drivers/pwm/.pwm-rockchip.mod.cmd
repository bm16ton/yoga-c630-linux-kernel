cmd_drivers/pwm/pwm-rockchip.mod := printf '%s\n'   pwm-rockchip.o | awk '!x[$$0]++ { print("drivers/pwm/"$$0) }' > drivers/pwm/pwm-rockchip.mod
