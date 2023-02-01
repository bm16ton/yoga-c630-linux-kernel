cmd_drivers/pwm/pwm-tegra.mod := printf '%s\n'   pwm-tegra.o | awk '!x[$$0]++ { print("drivers/pwm/"$$0) }' > drivers/pwm/pwm-tegra.mod
