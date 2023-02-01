cmd_drivers/media/rc/meson-ir.mod := printf '%s\n'   meson-ir.o | awk '!x[$$0]++ { print("drivers/media/rc/"$$0) }' > drivers/media/rc/meson-ir.mod
