cmd_lib/notifier-error-inject.mod := printf '%s\n'   notifier-error-inject.o | awk '!x[$$0]++ { print("lib/"$$0) }' > lib/notifier-error-inject.mod
