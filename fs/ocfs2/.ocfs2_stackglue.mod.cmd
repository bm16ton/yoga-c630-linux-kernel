cmd_fs/ocfs2/ocfs2_stackglue.mod := printf '%s\n'   stackglue.o | awk '!x[$$0]++ { print("fs/ocfs2/"$$0) }' > fs/ocfs2/ocfs2_stackglue.mod
