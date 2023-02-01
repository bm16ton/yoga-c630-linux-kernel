cmd_drivers/soc/qcom/qmi_helpers.mod := printf '%s\n'   qmi_encdec.o qmi_interface.o | awk '!x[$$0]++ { print("drivers/soc/qcom/"$$0) }' > drivers/soc/qcom/qmi_helpers.mod
