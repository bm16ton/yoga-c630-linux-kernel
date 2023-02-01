cmd_net/phonet/pn_pep.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/phonet/pn_pep.ko net/phonet/pn_pep.o net/phonet/pn_pep.mod.o;  true
