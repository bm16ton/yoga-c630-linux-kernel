adsprpcdir = $(libdir)
ADSP_CFLAGS = -fno-short-enums -U_DEBUG -DARM_ARCH_7A -DLE_ENABLE -DUSE_SYSLOG -Iinc -Isrc -DDEFAULT_DOMAIN_ID=0

adsprpc_LTLIBRARIES = libadsprpc.la
libadsprpc_la_SOURCES = fastrpc_apps_user.c \
		remotectl_stub.c \
		listener_android.c \
		adsp_current_process_stub.c \
		adsp_current_process1_stub.c \
		apps_std_skel.c \
		apps_std_imp.c \
		apps_mem_imp.c \
		apps_mem_skel.c \
		rpcmem_android.c \
		apps_remotectl_skel.c \
		std.c \
		std_path.c \
		std_mem.c \
		std_dtoa.c \
		std_strlprintf.c \
		BufBound.c \
		std_SwapBytes.c \
		smath.c \
		atomic.c \
		cae.c \
		adspmsgd_apps_skel.c \
		adspmsgd_adsp_stub.c \
		adspmsgd_adsp1_stub.c \
		adspmsgd_apps.c \
		platform_libs.c \
		pl_list.c \
		log_config.c \
		gpls.c \
		adsp_perf_stub.c \
		fastrpc_perf.c \
		mod_table.c

libadsprpc_la_LDFLAGS = -ldl -lpthread -lm -shared
libadsprpc_la_CFLAGS = -I$(top_srcdir)/inc $(ADSP_CFLAGS)

adsplistenerdir = $(libdir)
adsplistener_LTLIBRARIES = libadsp_default_listener.la
libadsp_default_listener_la_SOURCES = adsp_default_listener.c \
				adsp_default_listener_stub.c \
				std.c \
				std_mem.c
libadsp_default_listener_la_DEPENDENCIES = libadsprpc.la
libadsp_default_listener_la_LDFLAGS = $(top_builddir)/src/libadsprpc.la -ldl -lpthread -lm -shared
libadsp_default_listener_la_CFLAGS = -I$(top_srcdir)/inc $(ADSP_CFLAGS)

cdsprpcdir = $(libdir)

CDSP_CFLAGS = -fno-short-enums -U_DEBUG -DARM_ARCH_7A -DLE_ENABLE -DUSE_SYSLOG -Iinc -Isrc -DDEFAULT_DOMAIN_ID=3

cdsprpc_LTLIBRARIES = libcdsprpc.la
libcdsprpc_la_SOURCES = fastrpc_apps_user.c \
		remotectl_stub.c \
		listener_android.c \
		adsp_current_process_stub.c \
		adsp_current_process1_stub.c \
		apps_std_skel.c \
		apps_std_imp.c \
		apps_mem_imp.c \
		apps_mem_skel.c \
		rpcmem_android.c \
		apps_remotectl_skel.c \
		std.c \
		std_path.c \
		std_mem.c \
		std_dtoa.c \
		std_strlprintf.c \
		BufBound.c \
		std_SwapBytes.c \
		smath.c \
		atomic.c \
		cae.c \
		adspmsgd_apps_skel.c \
		adspmsgd_adsp_stub.c \
		adspmsgd_adsp1_stub.c \
		adspmsgd_apps.c \
		platform_libs.c \
		pl_list.c \
		log_config.c \
		gpls.c \
		adsp_perf_stub.c \
		fastrpc_perf.c \
		mod_table.c

libcdsprpc_la_LDFLAGS = -ldl -lpthread -lm -shared
libcdsprpc_la_CFLAGS = -I$(top_srcdir)/inc $(CDSP_CFLAGS)

cdsplistenerdir = $(libdir)
cdsplistener_LTLIBRARIES = libcdsp_default_listener.la
libcdsp_default_listener_la_SOURCES = adsp_default_listener.c \
				adsp_default_listener_stub.c \
				std.c \
				std_mem.c

libcdsp_default_listener_la_DEPENDENCIES = libcdsprpc.la
libcdsp_default_listener_la_LDFLAGS = $(top_builddir)/src/libcdsprpc.la -ldl -lpthread -lm -shared
libcdsp_default_listener_la_CFLAGS = -I$(top_srcdir)/inc  $(CDSP_CFLAGS)

bin_PROGRAMS = adsprpcd cdsprpcd

adsprpcddir = $(libdir)
adsprpcd_SOURCES = adsprpcd.c
adsprpcd_DEPENDENCIES = libadsp_default_listener.la
adsprpcd_CFLAGS = -I$(top_srcdir)/inc -DDEFAULT_DOMAIN_ID=0
adsprpcd_LDADD =  $(top_builddir)/src/libadsp_default_listener.la -lpthread -lm -ldl


cdsprpcddir = $(libdir)
cdsprpcd_SOURCES = cdsprpcd.c
cdsprpcd_DEPENDENCIES = libcdsp_default_listener.la
cdsprpcd_CFLAGS = -I$(top_srcdir)/inc -DDEFAULT_DOMAIN_ID=3
cdsprpcd_LDADD =  $(top_builddir)/src/libcdsp_default_listener.la -lpthread -lm -ldl

