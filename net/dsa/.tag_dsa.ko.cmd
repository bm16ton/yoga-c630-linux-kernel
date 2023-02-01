cmd_net/dsa/tag_dsa.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/dsa/tag_dsa.ko net/dsa/tag_dsa.o net/dsa/tag_dsa.mod.o;  true
