cmd_fs/quota/quota_v1.mod := printf '%s\n'   quota_v1.o | awk '!x[$$0]++ { print("fs/quota/"$$0) }' > fs/quota/quota_v1.mod
