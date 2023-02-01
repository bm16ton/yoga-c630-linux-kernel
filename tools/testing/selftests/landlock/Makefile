# SPDX-License-Identifier: GPL-2.0
<<<<<<< HEAD
#
# First run: make -C ../../../.. headers_install

CFLAGS += -Wall -O2 $(KHDR_INCLUDES)

LOCAL_HDRS += common.h

=======

CFLAGS += -Wall -O2 $(KHDR_INCLUDES)

>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
src_test := $(wildcard *_test.c)

TEST_GEN_PROGS := $(src_test:.c=)

TEST_GEN_PROGS_EXTENDED := true

<<<<<<< HEAD
# Short targets:
$(TEST_GEN_PROGS): LDLIBS += -lcap
$(TEST_GEN_PROGS_EXTENDED): LDFLAGS += -static

include ../lib.mk

# Targets with $(OUTPUT)/ prefix:
$(TEST_GEN_PROGS): LDLIBS += -lcap
$(TEST_GEN_PROGS_EXTENDED): LDFLAGS += -static
=======
OVERRIDE_TARGETS := 1
top_srcdir := ../../../..
include ../lib.mk

khdr_dir = $(top_srcdir)/usr/include

$(OUTPUT)/true: true.c
	$(LINK.c) $< $(LDLIBS) -o $@ -static

$(OUTPUT)/%_test: %_test.c $(khdr_dir)/linux/landlock.h ../kselftest_harness.h common.h
	$(LINK.c) $< $(LDLIBS) -o $@ -lcap -I$(khdr_dir)
>>>>>>> d161cce2b5c03920211ef59c968daf0e8fe12ce2
