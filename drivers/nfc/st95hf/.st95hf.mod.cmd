cmd_drivers/nfc/st95hf/st95hf.mod := printf '%s\n'   spi.o core.o | awk '!x[$$0]++ { print("drivers/nfc/st95hf/"$$0) }' > drivers/nfc/st95hf/st95hf.mod
