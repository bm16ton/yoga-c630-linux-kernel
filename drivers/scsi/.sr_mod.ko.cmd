cmd_drivers/scsi/sr_mod.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/scsi/sr_mod.ko drivers/scsi/sr_mod.o drivers/scsi/sr_mod.mod.o;  true
