cmd_block/bfq.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o block/bfq.ko block/bfq.o block/bfq.mod.o;  true
