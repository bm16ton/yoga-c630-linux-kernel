cmd_drivers/video/backlight/qcom-wled.mod := printf '%s\n'   qcom-wled.o | awk '!x[$$0]++ { print("drivers/video/backlight/"$$0) }' > drivers/video/backlight/qcom-wled.mod
