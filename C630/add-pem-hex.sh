#!/bin/bash
# /etc/portage/env/sys-kernel/gentoo-sources

{
    for cert in /lib/crda/pubkeys/*.x509.pem ; do
    echo $cert
        if [ -e "$cert" ]; then
            openssl x509 -in "$cert" -inform PEM &>/dev/null;
            if [ $? -eq 0 ]; then
                file=`basename "$cert"`
                echo "Adding wireless certificate to kernel sources ($file)"
                inc=${file%.x509.pem}
                openssl x509 -in "$cert" -inform PEM -outform DER | xxd -i -c 8 > "net/wireless/certs/${inc}".hex
            fi
        fi
    done
}
