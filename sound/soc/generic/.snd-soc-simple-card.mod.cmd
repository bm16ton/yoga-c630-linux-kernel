cmd_sound/soc/generic/snd-soc-simple-card.mod := printf '%s\n'   simple-card.o | awk '!x[$$0]++ { print("sound/soc/generic/"$$0) }' > sound/soc/generic/snd-soc-simple-card.mod
