cmd_drivers/char/hw_random/omap-rng.mod := printf '%s\n'   omap-rng.o | awk '!x[$$0]++ { print("drivers/char/hw_random/"$$0) }' > drivers/char/hw_random/omap-rng.mod
