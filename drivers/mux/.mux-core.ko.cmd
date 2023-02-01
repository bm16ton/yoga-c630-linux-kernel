cmd_drivers/mux/mux-core.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/mux/mux-core.ko drivers/mux/mux-core.o drivers/mux/mux-core.mod.o;  true
