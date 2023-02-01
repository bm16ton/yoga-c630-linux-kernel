cmd_drivers/char/hw_random/xgene-rng.mod := printf '%s\n'   xgene-rng.o | awk '!x[$$0]++ { print("drivers/char/hw_random/"$$0) }' > drivers/char/hw_random/xgene-rng.mod
