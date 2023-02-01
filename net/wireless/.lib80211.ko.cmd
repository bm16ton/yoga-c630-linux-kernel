cmd_net/wireless/lib80211.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o net/wireless/lib80211.ko net/wireless/lib80211.o net/wireless/lib80211.mod.o;  true
