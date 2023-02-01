cmd_drivers/char/hw_random/hisi-rng.mod := printf '%s\n'   hisi-rng.o | awk '!x[$$0]++ { print("drivers/char/hw_random/"$$0) }' > drivers/char/hw_random/hisi-rng.mod
