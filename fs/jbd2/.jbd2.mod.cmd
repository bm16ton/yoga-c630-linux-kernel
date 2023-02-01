cmd_fs/jbd2/jbd2.mod := printf '%s\n'   transaction.o commit.o recovery.o checkpoint.o revoke.o journal.o | awk '!x[$$0]++ { print("fs/jbd2/"$$0) }' > fs/jbd2/jbd2.mod
