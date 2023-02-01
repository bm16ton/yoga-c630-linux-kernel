cmd_drivers/scsi/pmcraid.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/scsi/pmcraid.ko drivers/scsi/pmcraid.o drivers/scsi/pmcraid.mod.o;  true
