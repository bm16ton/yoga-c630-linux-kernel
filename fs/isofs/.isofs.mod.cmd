cmd_fs/isofs/isofs.mod := printf '%s\n'   namei.o inode.o dir.o util.o rock.o export.o joliet.o compress.o | awk '!x[$$0]++ { print("fs/isofs/"$$0) }' > fs/isofs/isofs.mod
