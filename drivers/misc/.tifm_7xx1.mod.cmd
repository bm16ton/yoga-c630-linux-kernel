cmd_drivers/misc/tifm_7xx1.mod := printf '%s\n'   tifm_7xx1.o | awk '!x[$$0]++ { print("drivers/misc/"$$0) }' > drivers/misc/tifm_7xx1.mod
