cmd_sound/drivers/opl3/snd-opl3-synth.mod := printf '%s\n'   opl3_seq.o opl3_midi.o opl3_drums.o | awk '!x[$$0]++ { print("sound/drivers/opl3/"$$0) }' > sound/drivers/opl3/snd-opl3-synth.mod
