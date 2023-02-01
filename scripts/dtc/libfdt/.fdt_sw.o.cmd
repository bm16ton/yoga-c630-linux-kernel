cmd_scripts/dtc/libfdt/fdt_sw.o := gcc -Wp,-MMD,scripts/dtc/libfdt/.fdt_sw.o.d -Wall -Wmissing-prototypes -Wstrict-prototypes -O2 -fomit-frame-pointer -std=gnu11 -Wdeclaration-after-statement     -I ./scripts/dtc/libfdt -DNO_YAML  -c -o scripts/dtc/libfdt/fdt_sw.o scripts/dtc/libfdt/fdt_sw.c

source_scripts/dtc/libfdt/fdt_sw.o := scripts/dtc/libfdt/fdt_sw.c

deps_scripts/dtc/libfdt/fdt_sw.o := \
  scripts/dtc/libfdt/libfdt_env.h \
  scripts/dtc/libfdt/fdt.h \
  scripts/dtc/libfdt/libfdt.h \
  scripts/dtc/libfdt/libfdt_env.h \
  scripts/dtc/libfdt/fdt.h \
  scripts/dtc/libfdt/libfdt_internal.h \

scripts/dtc/libfdt/fdt_sw.o: $(deps_scripts/dtc/libfdt/fdt_sw.o)

$(deps_scripts/dtc/libfdt/fdt_sw.o):
