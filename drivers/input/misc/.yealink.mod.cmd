cmd_drivers/input/misc/yealink.mod := printf '%s\n'   yealink.o | awk '!x[$$0]++ { print("drivers/input/misc/"$$0) }' > drivers/input/misc/yealink.mod
