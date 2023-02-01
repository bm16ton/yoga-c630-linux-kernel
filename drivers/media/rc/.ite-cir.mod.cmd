cmd_drivers/media/rc/ite-cir.mod := printf '%s\n'   ite-cir.o | awk '!x[$$0]++ { print("drivers/media/rc/"$$0) }' > drivers/media/rc/ite-cir.mod
