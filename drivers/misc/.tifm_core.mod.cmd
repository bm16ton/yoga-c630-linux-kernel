cmd_drivers/misc/tifm_core.mod := printf '%s\n'   tifm_core.o | awk '!x[$$0]++ { print("drivers/misc/"$$0) }' > drivers/misc/tifm_core.mod
