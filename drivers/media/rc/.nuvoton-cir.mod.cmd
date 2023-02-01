cmd_drivers/media/rc/nuvoton-cir.mod := printf '%s\n'   nuvoton-cir.o | awk '!x[$$0]++ { print("drivers/media/rc/"$$0) }' > drivers/media/rc/nuvoton-cir.mod
