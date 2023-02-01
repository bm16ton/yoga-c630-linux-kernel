cmd_sound/drivers/opl3/snd-opl3-lib.mod := printf '%s\n'   opl3_lib.o opl3_synth.o | awk '!x[$$0]++ { print("sound/drivers/opl3/"$$0) }' > sound/drivers/opl3/snd-opl3-lib.mod
