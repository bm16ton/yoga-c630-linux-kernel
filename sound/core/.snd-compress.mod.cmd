cmd_sound/core/snd-compress.mod := printf '%s\n'   compress_offload.o | awk '!x[$$0]++ { print("sound/core/"$$0) }' > sound/core/snd-compress.mod
