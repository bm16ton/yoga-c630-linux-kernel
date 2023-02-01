cmd_drivers/usb/typec/ucsi/ucsi_acpi.mod := printf '%s\n'   ucsi_acpi.o | awk '!x[$$0]++ { print("drivers/usb/typec/ucsi/"$$0) }' > drivers/usb/typec/ucsi/ucsi_acpi.mod
