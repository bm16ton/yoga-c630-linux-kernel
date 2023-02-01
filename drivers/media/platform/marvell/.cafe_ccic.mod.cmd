cmd_drivers/media/platform/marvell/cafe_ccic.mod := printf '%s\n'   cafe-driver.o | awk '!x[$$0]++ { print("drivers/media/platform/marvell/"$$0) }' > drivers/media/platform/marvell/cafe_ccic.mod
