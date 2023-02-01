cmd_drivers/crypto/chelsio/chcr.mod := printf '%s\n'   chcr_core.o chcr_algo.o | awk '!x[$$0]++ { print("drivers/crypto/chelsio/"$$0) }' > drivers/crypto/chelsio/chcr.mod
