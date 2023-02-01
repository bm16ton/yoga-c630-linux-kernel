cmd_sound/core/snd-ctl-led.mod := printf '%s\n'   control_led.o | awk '!x[$$0]++ { print("sound/core/"$$0) }' > sound/core/snd-ctl-led.mod
