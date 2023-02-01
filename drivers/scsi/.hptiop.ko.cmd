cmd_drivers/scsi/hptiop.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/scsi/hptiop.ko drivers/scsi/hptiop.o drivers/scsi/hptiop.mod.o;  true
