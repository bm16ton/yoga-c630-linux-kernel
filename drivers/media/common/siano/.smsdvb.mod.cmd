cmd_drivers/media/common/siano/smsdvb.mod := printf '%s\n'   smsdvb-main.o | awk '!x[$$0]++ { print("drivers/media/common/siano/"$$0) }' > drivers/media/common/siano/smsdvb.mod
