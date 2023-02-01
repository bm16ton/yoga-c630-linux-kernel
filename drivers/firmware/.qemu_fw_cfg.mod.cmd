cmd_drivers/firmware/qemu_fw_cfg.mod := printf '%s\n'   qemu_fw_cfg.o | awk '!x[$$0]++ { print("drivers/firmware/"$$0) }' > drivers/firmware/qemu_fw_cfg.mod
