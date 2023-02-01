cmd_block/bfq.mod := printf '%s\n'   bfq-iosched.o bfq-wf2q.o bfq-cgroup.o | awk '!x[$$0]++ { print("block/"$$0) }' > block/bfq.mod
