cmd_sound/core/snd-hrtimer.mod := printf '%s\n'   hrtimer.o | awk '!x[$$0]++ { print("sound/core/"$$0) }' > sound/core/snd-hrtimer.mod
