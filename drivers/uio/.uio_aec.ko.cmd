cmd_drivers/uio/uio_aec.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/uio/uio_aec.ko drivers/uio/uio_aec.o drivers/uio/uio_aec.mod.o;  true
