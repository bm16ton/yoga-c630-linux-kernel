cmd_sound/core/snd-pcm-dmaengine.mod := printf '%s\n'   pcm_dmaengine.o | awk '!x[$$0]++ { print("sound/core/"$$0) }' > sound/core/snd-pcm-dmaengine.mod
