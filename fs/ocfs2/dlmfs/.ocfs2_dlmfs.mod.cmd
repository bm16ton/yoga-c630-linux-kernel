cmd_fs/ocfs2/dlmfs/ocfs2_dlmfs.mod := printf '%s\n'   userdlm.o dlmfs.o | awk '!x[$$0]++ { print("fs/ocfs2/dlmfs/"$$0) }' > fs/ocfs2/dlmfs/ocfs2_dlmfs.mod
