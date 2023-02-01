cmd_scripts/selinux/mdp/mdp := gcc -Wp,-MMD,scripts/selinux/mdp/.mdp.d -Wall -Wmissing-prototypes -Wstrict-prototypes -O2 -fomit-frame-pointer -std=gnu11 -Wdeclaration-after-statement     -I./include/uapi -I./include -I./security/selinux/include -I./include    -o scripts/selinux/mdp/mdp scripts/selinux/mdp/mdp.c   

source_scripts/selinux/mdp/mdp := scripts/selinux/mdp/mdp.c

deps_scripts/selinux/mdp/mdp := \
    $(wildcard include/config/EXT2_FS_SECURITY) \
    $(wildcard include/config/EXT4_FS_SECURITY) \
    $(wildcard include/config/EXT4_USE_FOR_EXT2) \
    $(wildcard include/config/JFS_SECURITY) \
    $(wildcard include/config/REISERFS_FS_SECURITY) \
    $(wildcard include/config/JFFS2_FS_SECURITY) \
    $(wildcard include/config/XFS_FS) \
    $(wildcard include/config/GFS2_FS) \
    $(wildcard include/config/BTRFS_FS) \
    $(wildcard include/config/F2FS_FS_SECURITY) \
    $(wildcard include/config/OCFS2_FS) \
    $(wildcard include/config/OVERLAY_FS) \
    $(wildcard include/config/SQUASHFS_XATTR) \
    $(wildcard include/config/UNIX98_PTYS) \
    $(wildcard include/config/HUGETLBFS) \
    $(wildcard include/config/TMPFS) \
    $(wildcard include/config/DEVTMPFS) \
    $(wildcard include/config/POSIX_MQUEUE) \
    $(wildcard include/config/PROC_FS) \
    $(wildcard include/config/SECURITY_SELINUX) \
    $(wildcard include/config/SYSFS) \
    $(wildcard include/config/DEBUG_FS) \
    $(wildcard include/config/TRACING) \
    $(wildcard include/config/PSTORE) \
  include/linux/kconfig.h \
    $(wildcard include/config/CPU_BIG_ENDIAN) \
    $(wildcard include/config/BOOGER) \
    $(wildcard include/config/FOO) \
  security/selinux/include/classmap.h \
  include/uapi/linux/capability.h \
  include/uapi/linux/types.h \
  include/uapi/linux/posix_types.h \
  include/uapi/linux/stddef.h \
  include/linux/compiler_types.h \
    $(wildcard include/config/DEBUG_INFO_BTF) \
    $(wildcard include/config/PAHOLE_HAS_BTF_TAG) \
    $(wildcard include/config/HAVE_ARCH_COMPILER_H) \
    $(wildcard include/config/CC_HAS_ASM_INLINE) \
  include/uapi/linux/socket.h \
  security/selinux/include/initial_sid_to_string.h \
  security/selinux/include/policycap_names.h \
  security/selinux/include/policycap.h \

scripts/selinux/mdp/mdp: $(deps_scripts/selinux/mdp/mdp)

$(deps_scripts/selinux/mdp/mdp):
