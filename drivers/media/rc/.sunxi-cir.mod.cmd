cmd_drivers/media/rc/sunxi-cir.mod := printf '%s\n'   sunxi-cir.o | awk '!x[$$0]++ { print("drivers/media/rc/"$$0) }' > drivers/media/rc/sunxi-cir.mod
