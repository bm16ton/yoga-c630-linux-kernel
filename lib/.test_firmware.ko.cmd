cmd_lib/test_firmware.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o lib/test_firmware.ko lib/test_firmware.o lib/test_firmware.mod.o;  true
