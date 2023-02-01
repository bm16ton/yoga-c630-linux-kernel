cmd_fs/fuse/virtiofs.mod := printf '%s\n'   virtio_fs.o | awk '!x[$$0]++ { print("fs/fuse/"$$0) }' > fs/fuse/virtiofs.mod
