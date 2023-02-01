cmd_fs/ocfs2/ocfs2_stack_user.mod := printf '%s\n'   stack_user.o | awk '!x[$$0]++ { print("fs/ocfs2/"$$0) }' > fs/ocfs2/ocfs2_stack_user.mod
