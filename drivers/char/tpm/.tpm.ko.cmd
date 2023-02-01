cmd_drivers/char/tpm/tpm.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/char/tpm/tpm.ko drivers/char/tpm/tpm.o drivers/char/tpm/tpm.mod.o;  true
