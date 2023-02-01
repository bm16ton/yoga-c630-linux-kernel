cmd_crypto/rmd160.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o crypto/rmd160.ko crypto/rmd160.o crypto/rmd160.mod.o;  true
