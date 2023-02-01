cmd_drivers/input/keyboard/qt2160.mod := printf '%s\n'   qt2160.o | awk '!x[$$0]++ { print("drivers/input/keyboard/"$$0) }' > drivers/input/keyboard/qt2160.mod
