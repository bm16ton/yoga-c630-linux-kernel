cmd_drivers/scsi/atp870u.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/scsi/atp870u.ko drivers/scsi/atp870u.o drivers/scsi/atp870u.mod.o;  true
