cmd_drivers/char/tpm/tpm_tis_core.mod := printf '%s\n'   tpm_tis_core.o | awk '!x[$$0]++ { print("drivers/char/tpm/"$$0) }' > drivers/char/tpm/tpm_tis_core.mod
