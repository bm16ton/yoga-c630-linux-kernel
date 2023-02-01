cmd_sound/core/seq/snd-seq-midi.mod := printf '%s\n'   seq_midi.o | awk '!x[$$0]++ { print("sound/core/seq/"$$0) }' > sound/core/seq/snd-seq-midi.mod
