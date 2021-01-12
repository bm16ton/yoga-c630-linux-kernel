#!/bin/bash
{
    for cert in /lib/crda/pubkeys/*.x509.pem; do
        openssl x509 -in $cert -outform der;
    done
} | hexdump -v -e '1/1 "0x%.2x," "\n"' > net/wireless/certs/$cert.hex
