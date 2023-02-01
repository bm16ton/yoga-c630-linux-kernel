cmd_drivers/media/rc/ir-rcmm-decoder.mod := printf '%s\n'   ir-rcmm-decoder.o | awk '!x[$$0]++ { print("drivers/media/rc/"$$0) }' > drivers/media/rc/ir-rcmm-decoder.mod
