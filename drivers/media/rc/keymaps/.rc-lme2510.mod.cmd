cmd_drivers/media/rc/keymaps/rc-lme2510.mod := printf '%s\n'   rc-lme2510.o | awk '!x[$$0]++ { print("drivers/media/rc/keymaps/"$$0) }' > drivers/media/rc/keymaps/rc-lme2510.mod
