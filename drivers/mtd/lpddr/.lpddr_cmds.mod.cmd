cmd_drivers/mtd/lpddr/lpddr_cmds.mod := printf '%s\n'   lpddr_cmds.o | awk '!x[$$0]++ { print("drivers/mtd/lpddr/"$$0) }' > drivers/mtd/lpddr/lpddr_cmds.mod
