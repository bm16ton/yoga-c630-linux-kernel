cmd_drivers/md/md-cluster.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/md/md-cluster.ko drivers/md/md-cluster.o drivers/md/md-cluster.mod.o;  true
