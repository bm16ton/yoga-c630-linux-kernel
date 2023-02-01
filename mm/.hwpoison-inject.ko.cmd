cmd_mm/hwpoison-inject.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o mm/hwpoison-inject.ko mm/hwpoison-inject.o mm/hwpoison-inject.mod.o;  true
