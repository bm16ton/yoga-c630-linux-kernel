cmd_drivers/firewire/nosy.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/firewire/nosy.ko drivers/firewire/nosy.o drivers/firewire/nosy.mod.o;  true
