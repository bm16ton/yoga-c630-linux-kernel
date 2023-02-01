cmd_drivers/media/rc/fintek-cir.mod := printf '%s\n'   fintek-cir.o | awk '!x[$$0]++ { print("drivers/media/rc/"$$0) }' > drivers/media/rc/fintek-cir.mod
