cmd_drivers/media/rc/ir-xmp-decoder.mod := printf '%s\n'   ir-xmp-decoder.o | awk '!x[$$0]++ { print("drivers/media/rc/"$$0) }' > drivers/media/rc/ir-xmp-decoder.mod
