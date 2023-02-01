cmd_mm/zsmalloc.mod := printf '%s\n'   zsmalloc.o | awk '!x[$$0]++ { print("mm/"$$0) }' > mm/zsmalloc.mod
