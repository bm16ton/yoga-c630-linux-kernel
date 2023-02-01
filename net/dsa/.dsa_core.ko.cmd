cmd_net/dsa/dsa_core.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/dsa/dsa_core.ko net/dsa/dsa_core.o net/dsa/dsa_core.mod.o;  true
