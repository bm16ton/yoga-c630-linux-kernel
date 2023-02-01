cmd_drivers/scsi/3w-9xxx.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/scsi/3w-9xxx.ko drivers/scsi/3w-9xxx.o drivers/scsi/3w-9xxx.mod.o;  true
