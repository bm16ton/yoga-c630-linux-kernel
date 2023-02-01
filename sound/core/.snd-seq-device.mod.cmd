cmd_sound/core/snd-seq-device.mod := printf '%s\n'   seq_device.o | awk '!x[$$0]++ { print("sound/core/"$$0) }' > sound/core/snd-seq-device.mod
