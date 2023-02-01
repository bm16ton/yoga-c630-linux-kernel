cmd_net/ife/ife.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/ife/ife.ko net/ife/ife.o net/ife/ife.mod.o;  true
