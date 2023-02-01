cmd_drivers/input/matrix-keymap.mod := printf '%s\n'   matrix-keymap.o | awk '!x[$$0]++ { print("drivers/input/"$$0) }' > drivers/input/matrix-keymap.mod
