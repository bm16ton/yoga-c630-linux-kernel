cmd_net/core/selftests.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/core/selftests.ko net/core/selftests.o net/core/selftests.mod.o;  true
