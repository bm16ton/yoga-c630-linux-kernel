cmd_drivers/pci/hotplug/acpiphp_ibm.mod := printf '%s\n'   acpiphp_ibm.o | awk '!x[$$0]++ { print("drivers/pci/hotplug/"$$0) }' > drivers/pci/hotplug/acpiphp_ibm.mod
