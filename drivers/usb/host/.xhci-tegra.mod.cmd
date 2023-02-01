cmd_drivers/usb/host/xhci-tegra.mod := printf '%s\n'   xhci-tegra.o | awk '!x[$$0]++ { print("drivers/usb/host/"$$0) }' > drivers/usb/host/xhci-tegra.mod
