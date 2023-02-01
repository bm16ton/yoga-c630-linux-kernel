cmd_crypto/asymmetric_keys/pkcs8_key_parser.mod := printf '%s\n'   pkcs8.asn1.o pkcs8_parser.o | awk '!x[$$0]++ { print("crypto/asymmetric_keys/"$$0) }' > crypto/asymmetric_keys/pkcs8_key_parser.mod
