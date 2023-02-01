cmd_drivers/input/misc/powermate.mod := printf '%s\n'   powermate.o | awk '!x[$$0]++ { print("drivers/input/misc/"$$0) }' > drivers/input/misc/powermate.mod
