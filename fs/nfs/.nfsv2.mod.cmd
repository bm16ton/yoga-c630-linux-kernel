cmd_fs/nfs/nfsv2.mod := printf '%s\n'   nfs2super.o proc.o nfs2xdr.o | awk '!x[$$0]++ { print("fs/nfs/"$$0) }' > fs/nfs/nfsv2.mod
