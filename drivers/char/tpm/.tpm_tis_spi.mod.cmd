cmd_drivers/char/tpm/tpm_tis_spi.mod := printf '%s\n'   tpm_tis_spi_main.o | awk '!x[$$0]++ { print("drivers/char/tpm/"$$0) }' > drivers/char/tpm/tpm_tis_spi.mod
