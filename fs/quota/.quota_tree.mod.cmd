cmd_fs/quota/quota_tree.mod := printf '%s\n'   quota_tree.o | awk '!x[$$0]++ { print("fs/quota/"$$0) }' > fs/quota/quota_tree.mod
