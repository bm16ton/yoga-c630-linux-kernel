cmd_sound/drivers/snd-serial-u16550.mod := printf '%s\n'   serial-u16550.o | awk '!x[$$0]++ { print("sound/drivers/"$$0) }' > sound/drivers/snd-serial-u16550.mod
