cmd_drivers/edac/thunderx_edac.mod := printf '%s\n'   thunderx_edac.o | awk '!x[$$0]++ { print("drivers/edac/"$$0) }' > drivers/edac/thunderx_edac.mod
