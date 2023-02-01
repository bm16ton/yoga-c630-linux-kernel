cmd_scripts/bin2c := gcc -Wp,-MMD,scripts/.bin2c.d -Wall -Wmissing-prototypes -Wstrict-prototypes -O2 -fomit-frame-pointer -std=gnu11 -Wdeclaration-after-statement         -o scripts/bin2c scripts/bin2c.c   

source_scripts/bin2c := scripts/bin2c.c

deps_scripts/bin2c := \

scripts/bin2c: $(deps_scripts/bin2c)

$(deps_scripts/bin2c):
