cmd_drivers/soc/amlogic/meson-canvas.mod := printf '%s\n'   meson-canvas.o | awk '!x[$$0]++ { print("drivers/soc/amlogic/"$$0) }' > drivers/soc/amlogic/meson-canvas.mod
