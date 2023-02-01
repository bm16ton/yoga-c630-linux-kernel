cmd_fs/ocfs2/ocfs2_stack_o2cb.mod := printf '%s\n'   stack_o2cb.o | awk '!x[$$0]++ { print("fs/ocfs2/"$$0) }' > fs/ocfs2/ocfs2_stack_o2cb.mod
