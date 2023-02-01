cmd_fs/hpfs/hpfs.mod := printf '%s\n'   alloc.o anode.o buffer.o dentry.o dir.o dnode.o ea.o file.o inode.o map.o name.o namei.o super.o | awk '!x[$$0]++ { print("fs/hpfs/"$$0) }' > fs/hpfs/hpfs.mod
