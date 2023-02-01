cmd_drivers/media/rc/ir-nec-decoder.mod := printf '%s\n'   ir-nec-decoder.o | awk '!x[$$0]++ { print("drivers/media/rc/"$$0) }' > drivers/media/rc/ir-nec-decoder.mod
