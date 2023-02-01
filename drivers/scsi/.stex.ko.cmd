cmd_drivers/scsi/stex.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/scsi/stex.ko drivers/scsi/stex.o drivers/scsi/stex.mod.o;  true
