cmd_drivers/staging/rtl8192e/rtllib_crypt_tkip.mod := printf '%s\n'   rtllib_crypt_tkip.o | awk '!x[$$0]++ { print("drivers/staging/rtl8192e/"$$0) }' > drivers/staging/rtl8192e/rtllib_crypt_tkip.mod
