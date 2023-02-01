cmd_drivers/accessibility/speakup/genmap.o := gcc -Wp,-MMD,drivers/accessibility/speakup/.genmap.o.d -Wall -Wmissing-prototypes -Wstrict-prototypes -O2 -fomit-frame-pointer -std=gnu11 -Wdeclaration-after-statement       -c -o drivers/accessibility/speakup/genmap.o drivers/accessibility/speakup/genmap.c

source_drivers/accessibility/speakup/genmap.o := drivers/accessibility/speakup/genmap.c

deps_drivers/accessibility/speakup/genmap.o := \
  drivers/accessibility/speakup/utils.h \
  drivers/accessibility/speakup/mapdata.h \

drivers/accessibility/speakup/genmap.o: $(deps_drivers/accessibility/speakup/genmap.o)

$(deps_drivers/accessibility/speakup/genmap.o):
