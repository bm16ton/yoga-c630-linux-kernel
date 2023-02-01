cmd_sound/core/snd-hwdep.mod := printf '%s\n'   hwdep.o | awk '!x[$$0]++ { print("sound/core/"$$0) }' > sound/core/snd-hwdep.mod
