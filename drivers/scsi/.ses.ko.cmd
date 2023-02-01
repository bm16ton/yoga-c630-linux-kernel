cmd_drivers/scsi/ses.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/scsi/ses.ko drivers/scsi/ses.o drivers/scsi/ses.mod.o;  true
