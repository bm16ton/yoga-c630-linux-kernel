cmd_drivers/accessibility/speakup/makemapdata.o := gcc -Wp,-MMD,drivers/accessibility/speakup/.makemapdata.o.d -Wall -Wmissing-prototypes -Wstrict-prototypes -O2 -fomit-frame-pointer -std=gnu11 -Wdeclaration-after-statement       -c -o drivers/accessibility/speakup/makemapdata.o drivers/accessibility/speakup/makemapdata.c

source_drivers/accessibility/speakup/makemapdata.o := drivers/accessibility/speakup/makemapdata.c

deps_drivers/accessibility/speakup/makemapdata.o := \
  drivers/accessibility/speakup/utils.h \

drivers/accessibility/speakup/makemapdata.o: $(deps_drivers/accessibility/speakup/makemapdata.o)

$(deps_drivers/accessibility/speakup/makemapdata.o):
