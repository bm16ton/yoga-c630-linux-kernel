cmd_sound/core/seq/snd-seq-dummy.mod := printf '%s\n'   seq_dummy.o | awk '!x[$$0]++ { print("sound/core/seq/"$$0) }' > sound/core/seq/snd-seq-dummy.mod
