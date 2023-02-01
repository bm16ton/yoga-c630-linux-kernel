cmd_sound/firewire/snd-isight.mod := printf '%s\n'   isight.o | awk '!x[$$0]++ { print("sound/firewire/"$$0) }' > sound/firewire/snd-isight.mod
