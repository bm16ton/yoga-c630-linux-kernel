cmd_net/dsa/tag_ocelot.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/dsa/tag_ocelot.ko net/dsa/tag_ocelot.o net/dsa/tag_ocelot.mod.o;  true
