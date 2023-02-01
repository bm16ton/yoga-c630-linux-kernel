cmd_drivers/net/phy/meson-gxl.mod := printf '%s\n'   meson-gxl.o | awk '!x[$$0]++ { print("drivers/net/phy/"$$0) }' > drivers/net/phy/meson-gxl.mod
