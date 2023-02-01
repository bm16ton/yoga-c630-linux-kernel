cmd_net/nfc/nfc_digital.mod := printf '%s\n'   digital_core.o digital_technology.o digital_dep.o | awk '!x[$$0]++ { print("net/nfc/"$$0) }' > net/nfc/nfc_digital.mod
