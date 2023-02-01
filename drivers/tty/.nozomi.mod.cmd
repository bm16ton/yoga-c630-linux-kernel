cmd_drivers/tty/nozomi.mod := printf '%s\n'   nozomi.o | awk '!x[$$0]++ { print("drivers/tty/"$$0) }' > drivers/tty/nozomi.mod
