cmd_drivers/input/keyboard/tegra-kbc.mod := printf '%s\n'   tegra-kbc.o | awk '!x[$$0]++ { print("drivers/input/keyboard/"$$0) }' > drivers/input/keyboard/tegra-kbc.mod
