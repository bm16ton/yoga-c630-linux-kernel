cmd_lib/memory-notifier-error-inject.mod := printf '%s\n'   memory-notifier-error-inject.o | awk '!x[$$0]++ { print("lib/"$$0) }' > lib/memory-notifier-error-inject.mod
