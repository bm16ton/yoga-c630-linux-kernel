cmd_sound/core/seq/snd-seq-midi-event.mod := printf '%s\n'   seq_midi_event.o | awk '!x[$$0]++ { print("sound/core/seq/"$$0) }' > sound/core/seq/snd-seq-midi-event.mod
