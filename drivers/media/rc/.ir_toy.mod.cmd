cmd_drivers/media/rc/ir_toy.mod := printf '%s\n'   ir_toy.o | awk '!x[$$0]++ { print("drivers/media/rc/"$$0) }' > drivers/media/rc/ir_toy.mod
