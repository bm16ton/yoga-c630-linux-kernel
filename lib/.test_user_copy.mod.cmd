cmd_lib/test_user_copy.mod := printf '%s\n'   test_user_copy.o | awk '!x[$$0]++ { print("lib/"$$0) }' > lib/test_user_copy.mod
