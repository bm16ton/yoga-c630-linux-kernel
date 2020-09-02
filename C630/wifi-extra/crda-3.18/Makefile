# Modify as you see fit, note this is built into crda,
# so if you change it here you will have to change crda.c
REG_BIN?=/usr/lib/crda/regulatory.bin
REG_GIT?=git://git.kernel.org/pub/scm/linux/kernel/git/sforshee/wireless-regdb.git

PREFIX ?= /usr/
MANDIR ?= $(PREFIX)/share/man/
INCLUDE_DIR ?= $(PREFIX)/include/reglib/
LIBDIR ?= $(PREFIX)/lib

SBINDIR ?= /sbin/

# Use a custom CRDA_UDEV_LEVEL when callling make install to
# change your desired level for the udev regulatory.rules
CRDA_UDEV_LEVEL?=85
UDEV_LEVEL=$(CRDA_UDEV_LEVEL)-
# You can customize this if your distributions uses
# a different location.
UDEV_RULE_DIR?=/lib/udev/rules.d/

# If your distribution requires a custom pubkeys dir
# you must update this variable to reflect where the
# keys are put when building. For example you can run
# with make PUBKEY_DIR=/usr/lib/crda/pubkeys
PUBKEY_DIR?=pubkeys
RUNTIME_PUBKEY_DIR?=/etc/wireless-regdb/pubkeys

PKG_CONFIG ?= pkg-config

CFLAGS += -O2 -fpic
CFLAGS += -std=gnu99 -Wall -Werror -pedantic
CFLAGS += -Wall -g
LDLIBREG += -lreg
LDLIBS += $(LDLIBREG)
LIBREGLDLIBS += -lm
LIBREG += libreg.so
LDFLAGS += -L ./

all: all_noverify verify

all_noverify: $(LIBREG) crda intersect regdbdump db2rd optimize

ifeq ($(USE_OPENSSL),1)
CFLAGS += -DUSE_OPENSSL -DPUBKEY_DIR=\"$(RUNTIME_PUBKEY_DIR)\" `$(PKG_CONFIG) --cflags openssl`
LIBREGLDLIBS += `$(PKG_CONFIG) --libs openssl`

ifeq ($(RUNTIME_PUBKEY_ONLY),1)
CFLAGS += -DRUNTIME_PUBKEY_ONLY
else
CFLAGS += -DHAVE_KEYS_SSL
$(LIBREG): keys-ssl.c
endif

else
CFLAGS += -DUSE_GCRYPT
LIBREGLDLIBS += -lgcrypt

$(LIBREG): keys-gcrypt.c

endif
MKDIR ?= mkdir -p
INSTALL ?= install

NL1FOUND := $(shell $(PKG_CONFIG) --atleast-version=1 libnl-1 && echo Y)
NL2FOUND := $(shell $(PKG_CONFIG) --atleast-version=2 libnl-2.0 && echo Y)
NL3FOUND := $(shell $(PKG_CONFIG) --atleast-version=3 libnl-3.0 && echo Y)
NL32FOUND := $(shell $(PKG_CONFIG) --atleast-version=3 libnl-3.2 && echo Y)

ifeq ($(NL32FOUND),Y)
CFLAGS += -DCONFIG_LIBNL30
NLLIBS += $(shell $(PKG_CONFIG) --libs libnl-genl-3.2)
NLLIBNAME = libnl-3.2
else
	ifeq ($(NL3FOUND),Y)
	CFLAGS += -DCONFIG_LIBNL30
	NLLIBS += $(shell $(PKG_CONFIG) --libs libnl-genl-3.0)
	NLLIBNAME = libnl-3.0
	else
		ifeq ($(NL2FOUND),Y)
		CFLAGS += -DCONFIG_LIBNL20
		NLLIBS += -lnl-genl
		NLLIBNAME = libnl-2.0
		else
			ifeq ($(NL1FOUND),Y)
			NLLIBNAME = libnl-1
			endif
		endif
	endif
endif

ifeq ($(NLLIBNAME),)
$(error Cannot find development files for any supported version of libnl)
endif

NLLIBS += `$(PKG_CONFIG) --libs $(NLLIBNAME)`
CFLAGS += `$(PKG_CONFIG) --cflags $(NLLIBNAME)`

ifeq ($(V),1)
Q=
NQ=@true
else
Q=@
NQ=@echo
endif

$(REG_BIN):
	$(NQ) '  EXIST ' $(REG_BIN)
	$(NQ)
	$(NQ) ERROR: The file: $(REG_BIN) is missing. You need this in place in order
	$(NQ) to verify CRDA. You can get it from:
	$(NQ)
	$(NQ) $(REG_GIT)
	$(NQ)
	$(NQ) "Once cloned (no need to build) cp regulatory.bin to $(REG_BIN)"
	$(NQ) "Use \"make noverify\" to disable verification"
	$(NQ)
	$(Q) exit 1

keys-%.c: utils/key2pub.py $(wildcard $(PUBKEY_DIR)/*.pem)
	$(NQ) '  GEN ' $@
	$(NQ) '  Trusted pubkeys:' $(wildcard $(PUBKEY_DIR)/*.pem)
	$(Q)./utils/key2pub.py --$* $(wildcard $(PUBKEY_DIR)/*.pem) $@

$(LIBREG): regdb.h reglib.h reglib.c
	$(NQ) '  CC  ' $@
	$(Q)$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -shared -Wl,-soname,$(LIBREG) $^ $(LIBREGLDLIBS)

install-libreg-headers:
	$(NQ) '  INSTALL  libreg-headers'
	$(Q)mkdir -p $(DESTDIR)/$(INCLUDE_DIR)
	$(Q)cp *.h $(DESTDIR)/$(INCLUDE_DIR)/

install-libreg:
	$(NQ) '  INSTALL  libreg'
	$(Q)mkdir -p $(DESTDIR)/$(LIBDIR)
	$(Q)cp $(LIBREG) $(DESTDIR)/$(LIBDIR)/
ifndef DESTDIR
	$(Q)ldconfig
endif

%.o: %.c regdb.h $(LIBREG)
	$(NQ) '  CC  ' $@
	$(Q)$(CC) -c $(CPPFLAGS) $(CFLAGS) -o $@ $<

crda: crda.o
	$(NQ) '  LD  ' $@
	$(Q)$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS) $(NLLIBS)

regdbdump: regdbdump.o
	$(NQ) '  LD  ' $@
	$(Q)$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)

intersect: intersect.o
	$(NQ) '  LD  ' $@
	$(Q)$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)

db2rd: db2rd.o
	$(NQ) '  LD  ' $@
	$(Q)$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)

optimize: optimize.o
	$(NQ) '  LD  ' $@
	$(Q)$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)

verify: $(REG_BIN) regdbdump
	$(NQ) '  CHK  $(REG_BIN)'
	$(Q)\
		LD_LIBRARY_PATH=.:$(LD_LIBRARY_PATH) \
		./regdbdump $(REG_BIN) >/dev/null

%.gz: %
	@$(NQ) ' GZIP' $<
	$(Q)gzip < $< > $@

install: install-libreg install-libreg-headers crda crda.8.gz regdbdump.8.gz
	$(NQ) '  INSTALL  crda'
	$(Q)$(MKDIR) $(DESTDIR)/$(SBINDIR)
	$(Q)$(INSTALL) -m 755 -t $(DESTDIR)/$(SBINDIR) crda
	$(NQ) '  INSTALL  regdbdump'
	$(Q)$(INSTALL) -m 755 -t $(DESTDIR)/$(SBINDIR) regdbdump
	$(NQ) '  INSTALL  $(UDEV_LEVEL)regulatory.rules'
	$(Q)$(MKDIR) $(DESTDIR)/$(UDEV_RULE_DIR)/
	@# This removes the old rule you may have, we were not
	@# putting it in the right place.
	$(Q)rm -f $(DESTDIR)/etc/udev/rules.d/regulatory.rules
	$(Q)sed 's:$$(SBINDIR):$(SBINDIR):' udev/regulatory.rules > udev/regulatory.rules.parsed
	$(Q)ln -sf regulatory.rules.parsed udev/$(UDEV_LEVEL)regulatory.rules
	$(Q)$(INSTALL) -m 644 -t \
		$(DESTDIR)/$(UDEV_RULE_DIR)/ \
		udev/$(UDEV_LEVEL)regulatory.rules
	$(NQ) '  INSTALL  crda.8.gz'
	$(Q)$(MKDIR) $(DESTDIR)$(MANDIR)/man8/
	$(Q)$(INSTALL) -m 644 -t $(DESTDIR)/$(MANDIR)/man8/ crda.8.gz
	$(NQ) '  INSTALL  regdbdump.8.gz'
	$(Q)$(INSTALL) -m 644 -t $(DESTDIR)/$(MANDIR)/man8/ regdbdump.8.gz

clean:
	$(Q)rm -f $(LIBREG) crda regdbdump intersect db2rd optimize \
		*.o *~ *.pyc keys-*.c *.gz \
	udev/$(UDEV_LEVEL)regulatory.rules udev/regulatory.rules.parsed
