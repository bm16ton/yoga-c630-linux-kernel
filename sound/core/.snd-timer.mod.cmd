cmd_sound/core/snd-timer.mod := printf '%s\n'   timer.o | awk '!x[$$0]++ { print("sound/core/"$$0) }' > sound/core/snd-timer.mod
