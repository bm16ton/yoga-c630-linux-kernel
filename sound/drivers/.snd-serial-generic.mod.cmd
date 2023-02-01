cmd_sound/drivers/snd-serial-generic.mod := printf '%s\n'   serial-generic.o | awk '!x[$$0]++ { print("sound/drivers/"$$0) }' > sound/drivers/snd-serial-generic.mod
