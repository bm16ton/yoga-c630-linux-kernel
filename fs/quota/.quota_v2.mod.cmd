cmd_fs/quota/quota_v2.mod := printf '%s\n'   quota_v2.o | awk '!x[$$0]++ { print("fs/quota/"$$0) }' > fs/quota/quota_v2.mod
