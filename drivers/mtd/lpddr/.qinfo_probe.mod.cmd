cmd_drivers/mtd/lpddr/qinfo_probe.mod := printf '%s\n'   qinfo_probe.o | awk '!x[$$0]++ { print("drivers/mtd/lpddr/"$$0) }' > drivers/mtd/lpddr/qinfo_probe.mod
