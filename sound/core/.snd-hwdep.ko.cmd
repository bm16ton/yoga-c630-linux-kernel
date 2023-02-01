cmd_sound/core/snd-hwdep.ko := ld -r  -EL  -maarch64elf -z noexecstack   --build-id=sha1  -T scripts/module.lds -o sound/core/snd-hwdep.ko sound/core/snd-hwdep.o sound/core/snd-hwdep.mod.o;  true
