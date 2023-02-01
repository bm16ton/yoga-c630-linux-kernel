cmd_drivers/media/rc/ir-sanyo-decoder.mod := printf '%s\n'   ir-sanyo-decoder.o | awk '!x[$$0]++ { print("drivers/media/rc/"$$0) }' > drivers/media/rc/ir-sanyo-decoder.mod
