cmd_drivers/misc/qcom-coincell.mod := printf '%s\n'   qcom-coincell.o | awk '!x[$$0]++ { print("drivers/misc/"$$0) }' > drivers/misc/qcom-coincell.mod
