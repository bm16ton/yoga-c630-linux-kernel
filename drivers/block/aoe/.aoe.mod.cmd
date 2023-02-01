cmd_drivers/block/aoe/aoe.mod := printf '%s\n'   aoeblk.o aoechr.o aoecmd.o aoedev.o aoemain.o aoenet.o | awk '!x[$$0]++ { print("drivers/block/aoe/"$$0) }' > drivers/block/aoe/aoe.mod
