cmd_lib/gen_crc64table := gcc -Wp,-MMD,lib/.gen_crc64table.d -Wall -Wmissing-prototypes -Wstrict-prototypes -O2 -fomit-frame-pointer -std=gnu11 -Wdeclaration-after-statement         -o lib/gen_crc64table lib/gen_crc64table.c   

source_lib/gen_crc64table := lib/gen_crc64table.c

deps_lib/gen_crc64table := \

lib/gen_crc64table: $(deps_lib/gen_crc64table)

$(deps_lib/gen_crc64table):
