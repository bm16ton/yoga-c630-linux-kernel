cmd_fs/nfs_common/nfs_acl.mod := printf '%s\n'   nfsacl.o | awk '!x[$$0]++ { print("fs/nfs_common/"$$0) }' > fs/nfs_common/nfs_acl.mod
