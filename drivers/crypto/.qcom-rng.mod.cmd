cmd_drivers/crypto/qcom-rng.mod := printf '%s\n'   qcom-rng.o | awk '!x[$$0]++ { print("drivers/crypto/"$$0) }' > drivers/crypto/qcom-rng.mod
