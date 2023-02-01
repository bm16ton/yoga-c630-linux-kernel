cmd_drivers/scsi/mvumi.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/scsi/mvumi.ko drivers/scsi/mvumi.o drivers/scsi/mvumi.mod.o;  true
