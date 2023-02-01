cmd_block/kyber-iosched.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o block/kyber-iosched.ko block/kyber-iosched.o block/kyber-iosched.mod.o;  true
