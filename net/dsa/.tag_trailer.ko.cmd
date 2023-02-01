cmd_net/dsa/tag_trailer.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/dsa/tag_trailer.ko net/dsa/tag_trailer.o net/dsa/tag_trailer.mod.o;  true
