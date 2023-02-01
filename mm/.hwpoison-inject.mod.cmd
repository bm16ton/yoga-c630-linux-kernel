cmd_mm/hwpoison-inject.mod := printf '%s\n'   hwpoison-inject.o | awk '!x[$$0]++ { print("mm/"$$0) }' > mm/hwpoison-inject.mod
