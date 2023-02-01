cmd_drivers/scsi/3w-sas.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/scsi/3w-sas.ko drivers/scsi/3w-sas.o drivers/scsi/3w-sas.mod.o;  true
