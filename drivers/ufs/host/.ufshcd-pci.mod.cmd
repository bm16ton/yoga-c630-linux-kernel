cmd_drivers/ufs/host/ufshcd-pci.mod := printf '%s\n'   ufshcd-pci.o | awk '!x[$$0]++ { print("drivers/ufs/host/"$$0) }' > drivers/ufs/host/ufshcd-pci.mod
