cmd_lib/crc7.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o lib/crc7.ko lib/crc7.o lib/crc7.mod.o;  true
