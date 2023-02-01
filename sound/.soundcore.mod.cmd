cmd_sound/soundcore.mod := printf '%s\n'   sound_core.o | awk '!x[$$0]++ { print("sound/"$$0) }' > sound/soundcore.mod
