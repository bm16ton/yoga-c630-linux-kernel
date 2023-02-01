cmd_drivers/slimbus/slim-qcom-ctrl.mod := printf '%s\n'   qcom-ctrl.o | awk '!x[$$0]++ { print("drivers/slimbus/"$$0) }' > drivers/slimbus/slim-qcom-ctrl.mod
