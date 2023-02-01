cmd_lib/lru_cache.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o lib/lru_cache.ko lib/lru_cache.o lib/lru_cache.mod.o;  true
