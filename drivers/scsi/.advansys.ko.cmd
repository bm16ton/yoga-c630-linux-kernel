cmd_drivers/scsi/advansys.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/scsi/advansys.ko drivers/scsi/advansys.o drivers/scsi/advansys.mod.o;  true
