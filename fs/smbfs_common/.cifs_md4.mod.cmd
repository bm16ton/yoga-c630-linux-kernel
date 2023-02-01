cmd_fs/smbfs_common/cifs_md4.mod := printf '%s\n'   cifs_md4.o | awk '!x[$$0]++ { print("fs/smbfs_common/"$$0) }' > fs/smbfs_common/cifs_md4.mod
