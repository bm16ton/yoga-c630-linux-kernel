cmd_lib/test-string_helpers.mod := printf '%s\n'   test-string_helpers.o | awk '!x[$$0]++ { print("lib/"$$0) }' > lib/test-string_helpers.mod
