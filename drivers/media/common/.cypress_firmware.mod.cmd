cmd_drivers/media/common/cypress_firmware.mod := printf '%s\n'   cypress_firmware.o | awk '!x[$$0]++ { print("drivers/media/common/"$$0) }' > drivers/media/common/cypress_firmware.mod
