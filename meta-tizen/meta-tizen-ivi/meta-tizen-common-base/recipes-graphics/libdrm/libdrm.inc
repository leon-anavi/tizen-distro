DESCRIPTION = "Userspace interface to kernel DRM services"
HOMEPAGE = "http://cgit.freedesktop.org/mesa/drm"
SECTION = "Graphics & UI Framework/Libraries"
LICENSE = "MIT"
PV = "2.4.52"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by libdrm


#PROVIDES by libdrm-intel
PROVIDES += "libdrm-intel"


#PROVIDES by libdrm-dev
PROVIDES += "libdrm-dev"


#PROVIDES by libkms
PROVIDES += "libkms"


#PROVIDES by libdrm-tools
PROVIDES += "libdrm-tools"
# the PROVIDES rules is ignore "libdrm = 2.4.52-0"
PROVIDES += "libdrm"
RPROVIDES_libdrm-tools += "libdrm"


RDEPENDS = ""
#RDEPENDS of libdrm-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "libdrm"
RDEPENDS_${PN}-dev += "libdrm-intel"
RDEPENDS_${PN}-dev += "libkms"


DEPENDS = ""
#DEPENDS of libdrm
DEPENDS += "libpciaccess"
DEPENDS += "libpthread-stubs"
inherit pkgconfig

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/libdrm.manifest .
 
 
}
do_patch_append() {
    bb.build.exec_func('do_prep', d)
}

do_configure() {
}

do_compile() {
 cd ${S}
  LANG=C
  export LANG
  unset DISPLAY
  LD_AS_NEEDED=1; export LD_AS_NEEDED ;
  
  
  autotools_do_configure
  
  oe_runmake ${PARALLEL_MAKE}
  oe_runmake ${PARALLEL_MAKE} -C tests dristat drmstat
  
  
  
}
EXTRA_OECONF += " --enable-static=yes --enable-udev --enable-libkms --disable-nouveau-experimental-api --disable-radeon --disable-nouveau --enable-exynos-experimental-api --enable-install-test-programs --disable-cairo-tests"

do_install() {
 export RPM_BUILD_ROOT=${D}
 cd ${S}
 LANG=C
 export LANG
 unset DISPLAY
 rm -rf ${D}
 mkdir -p ${D}
 
 
   oe_runmake \
         DESTDIR=${D} \
         INSTALL_ROOT=${D} \
         BINDIR=${prefix}/bin \
   install  
   rm -f ${D}${infodir}/dir 
   find ${D} -regex ".*\.la$" | xargs rm -f -- 
   find ${D} -regex ".*\.a$" | xargs rm -f --
 mkdir -p ${D}${prefix}/bin
 install  \
         tests/.libs/dristat \
         tests/.libs/drmstat \
         ${D}${prefix}/bin
 
 rm -f ${D}${prefix}/bin/kmstest
 
 
}

pkg_postinst_${PN}() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postinst_${PN}() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postinst_libkms() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_${PN}() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_${PN}() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_libkms() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " libdrm-tools "
PACKAGES += " libdrm-intel "
PACKAGES += " libdrm "
PACKAGES += " libkms "
PACKAGES += " libdrm-dev "

libdrm-tools_files = ""
libdrm-tools_files += "${prefix}/bin/dristat"
libdrm-tools_files += "${prefix}/bin/drmstat"
libdrm-tools_files += "${prefix}/bin/modeprint"
libdrm-tools_files += "${prefix}/bin/modetest"
MANIFESTFILES_${PN}-tools = "libdrm.manifest"

libdrm-intel_files = ""
libdrm-intel_files += "${prefix}/lib/libdrm_intel.so.*"
MANIFESTFILES_${PN}-intel = "libdrm.manifest"

libdrm_files = ""
libdrm_files += "${prefix}/lib/libdrm.so.*"
libdrm_files += "${prefix}/lib/libdrm_exynos.so.*"
libdrm_files += "${prefix}/lib/libdrm_vigs.so.*"
MANIFESTFILES_${PN} = "libdrm.manifest"

libkms_files = ""
libkms_files += "${prefix}/lib/libkms.so.*"
MANIFESTFILES_libkms = "libdrm.manifest"

libdrm-dev_files = ""
libdrm-dev_files += "${prefix}/include/libdrm"
libdrm-dev_files += "${prefix}/include/libdrm/*.h"
libdrm-dev_files += "${prefix}/include/libkms"
libdrm-dev_files += "${prefix}/include/libkms/*.h"
libdrm-dev_files += "${prefix}/include/exynos"
libdrm-dev_files += "${prefix}/include/exynos/*.h"
libdrm-dev_files += "${prefix}/include/*.h"
libdrm-dev_files += "${prefix}/lib/libdrm.so"
libdrm-dev_files += "${prefix}/lib/libdrm_intel.so"
libdrm-dev_files += "${prefix}/lib/libkms.so"
libdrm-dev_files += "${prefix}/lib/libdrm_exynos.so"
libdrm-dev_files += "${prefix}/lib/libdrm_vigs.so"
libdrm-dev_files += "${prefix}/lib/pkgconfig/*"
MANIFESTFILES_${PN}-dev = "libdrm.manifest"
DIRFILES_${PN}-dev = ""
DIRFILES_${PN}-dev += "${prefix}/include/libdrm"
DIRFILES_${PN}-dev += "${prefix}/include/libkms"
DIRFILES_${PN}-dev += "${prefix}/include/exynos"

FILES_${PN}-tools = "${libdrm-tools_files}"
FILES_${PN}-intel = "${libdrm-intel_files}"
FILES_${PN} = "${libdrm_files}"
FILES_libkms = "${libkms_files}"
FILES_${PN}-dev = "${libdrm-dev_files}"

PKG_libdrm-tools= "libdrm-tools"
PKG_libdrm-intel= "libdrm-intel"
PKG_libdrm= "libdrm"
PKG_libkms= "libkms"
PKG_libdrm-dev= "libdrm-dev"

require libdrm-extraconf.inc

