cmd_crypto/tea.mod := printf '%s\n'   tea.o | awk '!x[$$0]++ { print("crypto/"$$0) }' > crypto/tea.mod
