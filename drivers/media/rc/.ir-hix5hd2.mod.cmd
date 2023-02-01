cmd_drivers/media/rc/ir-hix5hd2.mod := printf '%s\n'   ir-hix5hd2.o | awk '!x[$$0]++ { print("drivers/media/rc/"$$0) }' > drivers/media/rc/ir-hix5hd2.mod
