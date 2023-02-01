cmd_drivers/scsi/libiscsi.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/scsi/libiscsi.ko drivers/scsi/libiscsi.o drivers/scsi/libiscsi.mod.o;  true
