cmd_drivers/char/hw_random/cn10k-rng.mod := printf '%s\n'   cn10k-rng.o | awk '!x[$$0]++ { print("drivers/char/hw_random/"$$0) }' > drivers/char/hw_random/cn10k-rng.mod
