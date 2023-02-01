cmd_lib/test_bpf.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o lib/test_bpf.ko lib/test_bpf.o lib/test_bpf.mod.o;  true
