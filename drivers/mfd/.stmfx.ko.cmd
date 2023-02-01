cmd_drivers/mfd/stmfx.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o drivers/mfd/stmfx.ko drivers/mfd/stmfx.o drivers/mfd/stmfx.mod.o;  true
