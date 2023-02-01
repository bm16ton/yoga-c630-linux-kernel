cmd_net/psample/psample.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/psample/psample.ko net/psample/psample.o net/psample/psample.mod.o;  true
