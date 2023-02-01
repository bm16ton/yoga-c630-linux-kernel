cmd_drivers/video/backlight/pwm_bl.mod := printf '%s\n'   pwm_bl.o | awk '!x[$$0]++ { print("drivers/video/backlight/"$$0) }' > drivers/video/backlight/pwm_bl.mod
