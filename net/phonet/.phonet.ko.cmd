cmd_net/phonet/phonet.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/phonet/phonet.ko net/phonet/phonet.o net/phonet/phonet.mod.o;  true
