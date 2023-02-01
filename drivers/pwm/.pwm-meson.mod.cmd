cmd_drivers/pwm/pwm-meson.mod := printf '%s\n'   pwm-meson.o | awk '!x[$$0]++ { print("drivers/pwm/"$$0) }' > drivers/pwm/pwm-meson.mod
