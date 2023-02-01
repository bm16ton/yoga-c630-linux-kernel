cmd_lib/pm-notifier-error-inject.mod := printf '%s\n'   pm-notifier-error-inject.o | awk '!x[$$0]++ { print("lib/"$$0) }' > lib/pm-notifier-error-inject.mod
