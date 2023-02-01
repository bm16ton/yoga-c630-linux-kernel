cmd_mm/z3fold.mod := printf '%s\n'   z3fold.o | awk '!x[$$0]++ { print("mm/"$$0) }' > mm/z3fold.mod
