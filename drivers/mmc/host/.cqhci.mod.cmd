cmd_drivers/mmc/host/cqhci.mod := printf '%s\n'   cqhci-core.o cqhci-crypto.o | awk '!x[$$0]++ { print("drivers/mmc/host/"$$0) }' > drivers/mmc/host/cqhci.mod
