cmd_scripts/dtc/libfdt/fdt_overlay.o := gcc -Wp,-MMD,scripts/dtc/libfdt/.fdt_overlay.o.d -Wall -Wmissing-prototypes -Wstrict-prototypes -O2 -fomit-frame-pointer -std=gnu11 -Wdeclaration-after-statement     -I ./scripts/dtc/libfdt -DNO_YAML  -c -o scripts/dtc/libfdt/fdt_overlay.o scripts/dtc/libfdt/fdt_overlay.c

source_scripts/dtc/libfdt/fdt_overlay.o := scripts/dtc/libfdt/fdt_overlay.c

deps_scripts/dtc/libfdt/fdt_overlay.o := \
  scripts/dtc/libfdt/libfdt_env.h \
  scripts/dtc/libfdt/fdt.h \
  scripts/dtc/libfdt/libfdt.h \
  scripts/dtc/libfdt/libfdt_env.h \
  scripts/dtc/libfdt/fdt.h \
  scripts/dtc/libfdt/libfdt_internal.h \

scripts/dtc/libfdt/fdt_overlay.o: $(deps_scripts/dtc/libfdt/fdt_overlay.o)

$(deps_scripts/dtc/libfdt/fdt_overlay.o):
