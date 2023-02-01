cmd_drivers/misc/bh1770glc.mod := printf '%s\n'   bh1770glc.o | awk '!x[$$0]++ { print("drivers/misc/"$$0) }' > drivers/misc/bh1770glc.mod
