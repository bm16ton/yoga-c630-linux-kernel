cmd_drivers/mmc/host/meson-gx-mmc.mod := printf '%s\n'   meson-gx-mmc.o | awk '!x[$$0]++ { print("drivers/mmc/host/"$$0) }' > drivers/mmc/host/meson-gx-mmc.mod
