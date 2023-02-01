cmd_lib/crc-itu-t.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o lib/crc-itu-t.ko lib/crc-itu-t.o lib/crc-itu-t.mod.o;  true
