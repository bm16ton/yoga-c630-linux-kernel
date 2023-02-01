cmd_drivers/media/rc/meson-ir-tx.mod := printf '%s\n'   meson-ir-tx.o | awk '!x[$$0]++ { print("drivers/media/rc/"$$0) }' > drivers/media/rc/meson-ir-tx.mod
