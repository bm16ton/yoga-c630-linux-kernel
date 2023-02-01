cmd_drivers/mmc/host/armmmci.mod := printf '%s\n'   mmci.o mmci_qcom_dml.o mmci_stm32_sdmmc.o | awk '!x[$$0]++ { print("drivers/mmc/host/"$$0) }' > drivers/mmc/host/armmmci.mod
