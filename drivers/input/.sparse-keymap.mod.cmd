cmd_drivers/input/sparse-keymap.mod := printf '%s\n'   sparse-keymap.o | awk '!x[$$0]++ { print("drivers/input/"$$0) }' > drivers/input/sparse-keymap.mod
