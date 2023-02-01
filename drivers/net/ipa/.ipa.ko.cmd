cmd_drivers/net/ipa/ipa.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/net/ipa/ipa.ko drivers/net/ipa/ipa.o drivers/net/ipa/ipa.mod.o;  true
