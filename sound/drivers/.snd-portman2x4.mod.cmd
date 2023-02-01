cmd_sound/drivers/snd-portman2x4.mod := printf '%s\n'   portman2x4.o | awk '!x[$$0]++ { print("sound/drivers/"$$0) }' > sound/drivers/snd-portman2x4.mod
