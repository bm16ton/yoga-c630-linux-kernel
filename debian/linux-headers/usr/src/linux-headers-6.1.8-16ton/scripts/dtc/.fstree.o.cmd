cmd_scripts/dtc/fstree.o := gcc -Wp,-MMD,scripts/dtc/.fstree.o.d -Wall -Wmissing-prototypes -Wstrict-prototypes -O2 -fomit-frame-pointer -std=gnu11 -Wdeclaration-after-statement     -I ./scripts/dtc/libfdt -DNO_YAML  -c -o scripts/dtc/fstree.o scripts/dtc/fstree.c

source_scripts/dtc/fstree.o := scripts/dtc/fstree.c

deps_scripts/dtc/fstree.o := \
  scripts/dtc/dtc.h \
  scripts/dtc/libfdt/libfdt_env.h \
  scripts/dtc/libfdt/fdt.h \
  scripts/dtc/util.h \

scripts/dtc/fstree.o: $(deps_scripts/dtc/fstree.o)

$(deps_scripts/dtc/fstree.o):
