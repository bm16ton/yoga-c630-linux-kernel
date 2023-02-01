cmd_mm/z3fold.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o mm/z3fold.ko mm/z3fold.o mm/z3fold.mod.o;  true
