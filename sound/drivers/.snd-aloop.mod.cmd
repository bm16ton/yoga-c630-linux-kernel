cmd_sound/drivers/snd-aloop.mod := printf '%s\n'   aloop.o | awk '!x[$$0]++ { print("sound/drivers/"$$0) }' > sound/drivers/snd-aloop.mod
