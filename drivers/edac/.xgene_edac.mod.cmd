cmd_drivers/edac/xgene_edac.mod := printf '%s\n'   xgene_edac.o | awk '!x[$$0]++ { print("drivers/edac/"$$0) }' > drivers/edac/xgene_edac.mod
