cmd_drivers/media/common/cx2341x.mod := printf '%s\n'   cx2341x.o | awk '!x[$$0]++ { print("drivers/media/common/"$$0) }' > drivers/media/common/cx2341x.mod
