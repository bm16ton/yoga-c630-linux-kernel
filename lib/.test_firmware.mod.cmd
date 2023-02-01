cmd_lib/test_firmware.mod := printf '%s\n'   test_firmware.o | awk '!x[$$0]++ { print("lib/"$$0) }' > lib/test_firmware.mod
