cmd_drivers/media/rc/iguanair.mod := printf '%s\n'   iguanair.o | awk '!x[$$0]++ { print("drivers/media/rc/"$$0) }' > drivers/media/rc/iguanair.mod
