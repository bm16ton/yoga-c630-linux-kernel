-----BEGIN PGP SIGNED MESSAGE-----
Hash: SHA512

Format: 1.0
Source: mesa
Binary: libxatracker2, libxatracker-dev, libd3dadapter9-mesa, libd3dadapter9-mesa-dev, libgbm1, libgbm-dev, libegl-mesa0, libegl1-mesa, libegl1-mesa-dev, libwayland-egl1-mesa, libgles2-mesa, libgles2-mesa-dev, libglapi-mesa, libglx-mesa0, libgl1-mesa-glx, libgl1-mesa-dri, libgl1-mesa-dev, mesa-common-dev, libosmesa6, libosmesa6-dev, mesa-va-drivers, mesa-vdpau-drivers, mesa-vulkan-drivers, mesa-opencl-icd
Architecture: any
Version: 20.1.0-1
Maintainer: Debian X Strike Force <debian-x@lists.debian.org>
Uploaders: Andreas Boll <aboll@debian.org>
Homepage: https://mesa3d.org/
Standards-Version: 4.1.4
Vcs-Browser: https://salsa.debian.org/xorg-team/lib/mesa
Vcs-Git: https://salsa.debian.org/xorg-team/lib/mesa.git
Build-Depends: debhelper-compat (= 12), glslang-tools [amd64 arm64 armel armhf i386 mips64el mipsel powerpc ppc64 ppc64el s390x sparc64 x32], meson (>= 0.45), quilt (>= 0.63-8.2~), pkg-config, libdrm-dev (>= 2.4.101) [!hurd-any], libx11-dev, libxxf86vm-dev, libexpat1-dev, libsensors-dev [!hurd-any], libxfixes-dev, libxdamage-dev, libxext-dev, libva-dev (>= 1.6.0) [linux-any kfreebsd-any] <!pkg.mesa.nolibva>, libvdpau-dev (>= 1.1.1) [linux-any kfreebsd-any], libvulkan-dev [amd64 arm64 armel armhf i386 mips64el mipsel powerpc ppc64 ppc64el s390x sparc64 x32], x11proto-dev, linux-libc-dev (>= 2.6.31) [linux-any], libx11-xcb-dev, libxcb-dri2-0-dev (>= 1.8), libxcb-glx0-dev (>= 1.8.1), libxcb-xfixes0-dev, libxcb-dri3-dev, libxcb-present-dev, libxcb-randr0-dev, libxcb-sync-dev, libxrandr-dev, libxshmfence-dev (>= 1.1), libzstd-dev, python3, python3-mako, python3-setuptools, flex, bison, libelf-dev [amd64 arm64 armel armhf i386 kfreebsd-amd64 kfreebsd-i386 mips64el mipsel powerpc ppc64 ppc64el s390x sparc64], libwayland-dev (>= 1.15.0) [linux-any], libwayland-egl-backend-dev (>= 1.15.0) [linux-any], llvm-10-dev (>= 1:10.0.0-4~) [amd64 arm64 armel armhf i386 kfreebsd-amd64 kfreebsd-i386 mips64el mipsel powerpc ppc64 ppc64el s390x sparc64], libclang-10-dev (>= 1:10.0.0-4~) [amd64 arm64 armel armhf i386 kfreebsd-amd64 kfreebsd-i386 mips64el mipsel powerpc ppc64 ppc64el s390x sparc64], libclc-dev (>= 0.2.0+git20190827-5~) [amd64 arm64 armel armhf i386 kfreebsd-amd64 kfreebsd-i386 mips64el mipsel powerpc ppc64 ppc64el s390x sparc64], wayland-protocols (>= 1.9), zlib1g-dev, libglvnd-dev (>= 1.3.0)
Package-List:
 libd3dadapter9-mesa deb libs optional arch=amd64,arm64,armel,armhf,i386,kfreebsd-i386,powerpc
 libd3dadapter9-mesa-dev deb libdevel optional arch=amd64,arm64,armel,armhf,i386,kfreebsd-i386,powerpc
 libegl-mesa0 deb libs optional arch=any
 libegl1-mesa deb oldlibs optional arch=any
 libegl1-mesa-dev deb libdevel optional arch=any
 libgbm-dev deb libdevel optional arch=linux-any,kfreebsd-any
 libgbm1 deb libs optional arch=linux-any,kfreebsd-any
 libgl1-mesa-dev deb oldlibs optional arch=any
 libgl1-mesa-dri deb libs optional arch=any
 libgl1-mesa-glx deb oldlibs optional arch=any
 libglapi-mesa deb libs optional arch=any
 libgles2-mesa deb oldlibs optional arch=any
 libgles2-mesa-dev deb oldlibs optional arch=any
 libglx-mesa0 deb libs optional arch=any
 libosmesa6 deb libs optional arch=any
 libosmesa6-dev deb libdevel optional arch=any
 libwayland-egl1-mesa deb oldlibs optional arch=linux-any
 libxatracker-dev deb libdevel optional arch=amd64,i386,x32
 libxatracker2 deb libs optional arch=amd64,i386,x32
 mesa-common-dev deb libdevel optional arch=any
 mesa-opencl-icd deb libs optional arch=amd64,arm64,armel,armhf,i386,kfreebsd-amd64,kfreebsd-i386,mips64el,mipsel,powerpc,ppc64,ppc64el,s390x,sparc64
 mesa-va-drivers deb libs optional arch=linux-any,kfreebsd-any profile=!pkg.mesa.nolibva
 mesa-vdpau-drivers deb libs optional arch=linux-any,kfreebsd-any
 mesa-vulkan-drivers deb libs optional arch=amd64,arm64,armel,armhf,i386,mips64el,mipsel,powerpc,ppc64,ppc64el,s390x,sparc64,x32
Checksums-Sha1:
 cd7ee11c3e7fa5ed25ba4da94841c276d70bb1aa 19623586 mesa_20.1.0.orig.tar.gz
 0032c5183487aee678c3b52e067807e49c8e95c1 107332 mesa_20.1.0-1.diff.gz
Checksums-Sha256:
 9c1cbb3bed46453c3b0c1fdc841476d53f92b81170982b6db30097027a4cfe2b 19623586 mesa_20.1.0.orig.tar.gz
 1afadff4fd56ade0c79288cf52f3dd1a4bfa1e1e36e2dca77e1bf5fdb1589927 107332 mesa_20.1.0-1.diff.gz
Files:
 1ba4447bc7be3c5de45660e990e44e11 19623586 mesa_20.1.0.orig.tar.gz
 4a8f7efa10425ddea0941106bab95884 107332 mesa_20.1.0-1.diff.gz

-----BEGIN PGP SIGNATURE-----

iQIzBAEBCgAdFiEEdS3ifE3rFwGbS2Yjy3AxZaiJhNwFAl7Pj54ACgkQy3AxZaiJ
hNxxthAAkoGZjYKUOe+PJvCaOWUfXTqKN8Wjswlxo2RIWDcU1MuXisvPvGcg0ohE
Xui6Ujfaw1G+QXlhHaJU1JXiNyQmAJkso/1RyrTOexowyG1CLE5ekkSk/zWbORkj
UpROhdN6dvPzve/WNXk6QKjjRUIT6x8tW6LDi/dBhauuQ27Z+f4UhWdKRXRObqS3
wIfBcEKuassX/9RbO/BYGDM5TYR0JaoWyGfAgO4myH3LZP8PcLB5E7K6HT39p6x/
wjgW9zDIk1l2zVSVxYWqf58SVuoya+y+JyqjxLjvBbVjj9zsFslDwSz4T+xjLIUs
K/JStSx+WfKDnYcUXVVAEKCwo2xFuj02DFmEvUmmbAyNQFxPSvUyC8GK44tzTq97
jg14fi/x02xmKptwsFDYTTZWQtTYuJUqVLqolKMvuxI+NHPcErlkKSzSFHHltSEw
ZrR4KmJlqNPOaO9ZYaRPk3S5ojJH26RaAlLb32ESuFezHKLQ5FoqmvDrYlZfp3nk
MxSzPR2HtGuNCTUhZJDYj0OjGoU9sJOePLS7Xr5E9gq+vzG1ciCGBRoTb8mkizh0
fx40S+8W6gGJfH2yf1HGfUBFBKLCDje+NB//cH3W5RrKl/+4PvLRfbdOS6IRRhh3
ooZ0ugG2RDG7qOU6A/q1pMW02KJB9iAnlpRE5u4w6xyJMyHCv1g=
=UngS
-----END PGP SIGNATURE-----
