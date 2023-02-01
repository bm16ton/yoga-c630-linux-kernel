cmd_drivers/tty/n_gsm.mod := printf '%s\n'   n_gsm.o | awk '!x[$$0]++ { print("drivers/tty/"$$0) }' > drivers/tty/n_gsm.mod
