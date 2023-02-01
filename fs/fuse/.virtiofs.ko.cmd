cmd_fs/fuse/virtiofs.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o fs/fuse/virtiofs.ko fs/fuse/virtiofs.o fs/fuse/virtiofs.mod.o;  true
