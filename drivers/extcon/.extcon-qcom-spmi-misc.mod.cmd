cmd_drivers/extcon/extcon-qcom-spmi-misc.mod := printf '%s\n'   extcon-qcom-spmi-misc.o | awk '!x[$$0]++ { print("drivers/extcon/"$$0) }' > drivers/extcon/extcon-qcom-spmi-misc.mod
