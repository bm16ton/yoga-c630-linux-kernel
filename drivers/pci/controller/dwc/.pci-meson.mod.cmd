cmd_drivers/pci/controller/dwc/pci-meson.mod := printf '%s\n'   pci-meson.o | awk '!x[$$0]++ { print("drivers/pci/controller/dwc/"$$0) }' > drivers/pci/controller/dwc/pci-meson.mod
