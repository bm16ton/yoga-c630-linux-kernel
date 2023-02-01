cmd_drivers/rtc/rtc-meson-vrtc.mod := printf '%s\n'   rtc-meson-vrtc.o | awk '!x[$$0]++ { print("drivers/rtc/"$$0) }' > drivers/rtc/rtc-meson-vrtc.mod
