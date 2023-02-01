cmd_drivers/media/rc/keymaps/rc-mecool-kii-pro.mod := printf '%s\n'   rc-mecool-kii-pro.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-mecool-kii-pro.mod
