cmd_sound/core/snd-rawmidi.mod := printf '%s\n'   rawmidi.o | awk '!x[$$0]++ { print("sound/core/"$$0) }' > sound/core/snd-rawmidi.mod
