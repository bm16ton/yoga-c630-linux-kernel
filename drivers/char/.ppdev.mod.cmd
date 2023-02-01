cmd_drivers/char/ppdev.mod := printf '%s\n'   ppdev.o | awk '!x[$$0]++ { print("drivers/char/"$$0) }' > drivers/char/ppdev.mod
