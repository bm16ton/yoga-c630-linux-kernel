cmd_lib/math/cordic.mod := printf '%s\n'   cordic.o | awk '!x[$$0]++ { print("lib/math/"$$0) }' > lib/math/cordic.mod
