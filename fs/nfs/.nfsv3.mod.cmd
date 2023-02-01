cmd_fs/nfs/nfsv3.mod := printf '%s\n'   nfs3super.o nfs3client.o nfs3proc.o nfs3xdr.o nfs3acl.o | awk '!x[$$0]++ { print("fs/nfs/"$$0) }' > fs/nfs/nfsv3.mod
