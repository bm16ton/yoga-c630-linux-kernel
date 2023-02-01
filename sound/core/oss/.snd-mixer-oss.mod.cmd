cmd_sound/core/oss/snd-mixer-oss.mod := printf '%s\n'   mixer_oss.o | awk '!x[$$0]++ { print("sound/core/oss/"$$0) }' > sound/core/oss/snd-mixer-oss.mod
