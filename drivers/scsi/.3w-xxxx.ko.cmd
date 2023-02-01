cmd_drivers/scsi/3w-xxxx.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/scsi/3w-xxxx.ko drivers/scsi/3w-xxxx.o drivers/scsi/3w-xxxx.mod.o;  true
