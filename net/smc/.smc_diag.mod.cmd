cmd_net/smc/smc_diag.mod := printf '%s\n'   smc_diag.o | awk '!x[$$0]++ { print("net/smc/"$$0) }' > net/smc/smc_diag.mod
