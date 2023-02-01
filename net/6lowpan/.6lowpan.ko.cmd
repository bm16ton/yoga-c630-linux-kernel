cmd_net/6lowpan/6lowpan.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/6lowpan/6lowpan.ko net/6lowpan/6lowpan.o net/6lowpan/6lowpan.mod.o;  true
