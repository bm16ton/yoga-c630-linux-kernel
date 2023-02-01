cmd_sound/ac97_bus.mod := printf '%s\n'   ac97_bus.o | awk '!x[$$0]++ { print("sound/"$$0) }' > sound/ac97_bus.mod
