cmd_drivers/char/tpm/tpm_vtpm_proxy.mod := printf '%s\n'   tpm_vtpm_proxy.o | awk '!x[$$0]++ { print("drivers/char/tpm/"$$0) }' > drivers/char/tpm/tpm_vtpm_proxy.mod
