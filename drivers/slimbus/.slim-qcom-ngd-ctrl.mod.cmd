cmd_drivers/slimbus/slim-qcom-ngd-ctrl.mod := printf '%s\n'   qcom-ngd-ctrl.o | awk '!x[$$0]++ { print("drivers/slimbus/"$$0) }' > drivers/slimbus/slim-qcom-ngd-ctrl.mod
