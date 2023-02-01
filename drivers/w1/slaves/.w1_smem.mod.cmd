cmd_drivers/w1/slaves/w1_smem.mod := printf '%s\n'   w1_smem.o | awk '!x[$$0]++ { print("drivers/w1/slaves/"$$0) }' > drivers/w1/slaves/w1_smem.mod
