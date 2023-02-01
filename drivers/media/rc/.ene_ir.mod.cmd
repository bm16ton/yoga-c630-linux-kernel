cmd_drivers/media/rc/ene_ir.mod := printf '%s\n'   ene_ir.o | awk '!x[$$0]++ { print("drivers/media/rc/"$$0) }' > drivers/media/rc/ene_ir.mod
