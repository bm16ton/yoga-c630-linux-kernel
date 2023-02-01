cmd_lib/ts_fsm.mod := printf '%s\n'   ts_fsm.o | awk '!x[$$0]++ { print("lib/"$$0) }' > lib/ts_fsm.mod
