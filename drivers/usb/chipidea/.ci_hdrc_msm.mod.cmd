cmd_drivers/usb/chipidea/ci_hdrc_msm.mod := printf '%s\n'   ci_hdrc_msm.o | awk '!x[$$0]++ { print("drivers/usb/chipidea/"$$0) }' > drivers/usb/chipidea/ci_hdrc_msm.mod
