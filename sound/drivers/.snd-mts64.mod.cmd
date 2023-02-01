cmd_sound/drivers/snd-mts64.mod := printf '%s\n'   mts64.o | awk '!x[$$0]++ { print("sound/drivers/"$$0) }' > sound/drivers/snd-mts64.mod
