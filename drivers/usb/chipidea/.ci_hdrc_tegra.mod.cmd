cmd_drivers/usb/chipidea/ci_hdrc_tegra.mod := printf '%s\n'   ci_hdrc_tegra.o | awk '!x[$$0]++ { print("drivers/usb/chipidea/"$$0) }' > drivers/usb/chipidea/ci_hdrc_tegra.mod
