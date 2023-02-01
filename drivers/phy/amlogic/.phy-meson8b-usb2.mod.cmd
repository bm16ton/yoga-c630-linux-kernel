cmd_drivers/phy/amlogic/phy-meson8b-usb2.mod := printf '%s\n'   phy-meson8b-usb2.o | awk '!x[$$0]++ { print("drivers/phy/amlogic/"$$0) }' > drivers/phy/amlogic/phy-meson8b-usb2.mod
