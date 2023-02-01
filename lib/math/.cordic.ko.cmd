cmd_lib/math/cordic.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o lib/math/cordic.ko lib/math/cordic.o lib/math/cordic.mod.o;  true
