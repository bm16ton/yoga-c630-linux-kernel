cmd_drivers/media/rc/ir-mce_kbd-decoder.mod := printf '%s\n'   ir-mce_kbd-decoder.o | awk '!x[$$0]++ { print("drivers/media/rc/"$$0) }' > drivers/media/rc/ir-mce_kbd-decoder.mod
