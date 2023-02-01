cmd_drivers/media/platform/marvell/mcam-core.mod := printf '%s\n'   mcam-core.o | awk '!x[$$0]++ { print("drivers/media/platform/marvell/"$$0) }' > drivers/media/platform/marvell/mcam-core.mod
