cmd_drivers/misc/tsl2550.mod := printf '%s\n'   tsl2550.o | awk '!x[$$0]++ { print("drivers/misc/"$$0) }' > drivers/misc/tsl2550.mod
