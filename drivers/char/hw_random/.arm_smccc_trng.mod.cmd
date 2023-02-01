cmd_drivers/char/hw_random/arm_smccc_trng.mod := printf '%s\n'   arm_smccc_trng.o | awk '!x[$$0]++ { print("drivers/char/hw_random/"$$0) }' > drivers/char/hw_random/arm_smccc_trng.mod
