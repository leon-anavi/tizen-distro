DESCRIPTION = "WebSocket Library"
HOMEPAGE = "http://nohomepage.org"
SECTION = "System/Libraries"
LICENSE = "LGPL-2.1"
PV = "1.2"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by libwebsockets


#PROVIDES by libwebsockets-dev
PROVIDES += "libwebsockets-dev"


RDEPENDS = ""
#RDEPENDS of libwebsockets (${PN})
RDEPENDS_${PN} += "glibc"

#RDEPENDS of libwebsockets-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "libwebsockets"


DEPENDS = ""
#DEPENDS of libwebsockets
DEPENDS += "systemd"
DEPENDS += "zlib"
inherit tizen_cmake
DEPENDS += "openssl"
inherit pkgconfig

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q -n libwebsockets-1.2
 cp ${S}/packaging/libwebsockets.manifest .
 
 
 
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
 
 
 
   cmake \
         -DCMAKE_VERBOSE_MAKEFILE=ON \
         -DCMAKE_INSTALL_PREFIX:PATH=${prefix} \
         -DCMAKE_INSTALL_LIBDIR:PATH=${prefix}/lib \
         -DINCLUDE_INSTALL_DIR:PATH=${prefix}/include \
         -DLIB_INSTALL_DIR:PATH=${prefix}/lib \
         -DSYSCONF_INSTALL_DIR:PATH=${sysconfdir} \
         -DSHARE_INSTALL_PREFIX:PATH=${prefix}/share \
         -DCMAKE_SKIP_RPATH:BOOL=ON \
         -DBUILD_SHARED_LIBS:BOOL=ON \
         -DCMAKE_TOOLCHAIN_FILE=${WORKDIR}/toolchain.cmake \
         ${EXTRA_OECMAKE} -DWITH_SSL=On -DWITH_SD_DAEMON=ON
 
 oe_runmake ${PARALLEL_MAKE}
 
 
 
}

do_install() {
 export RPM_BUILD_ROOT=${D}
 cd ${S}
 LANG=C
 export LANG
 unset DISPLAY
 rm -rf ${D}
 mkdir -p ${D}
 
 rm -rf ${D}
 
   oe_runmake \
         DESTDIR=${D} \
         INSTALL_ROOT=${D} \
         BINDIR=${prefix}/bin \
   install  
   rm -f ${D}${infodir}/dir 
   find ${D} -regex ".*\.la$" | xargs rm -f -- 
   find ${D} -regex ".*\.a$" | xargs rm -f --
 
 
}

pkg_postinst_${PN}() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_${PN}() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " libwebsockets "
PACKAGES += " libwebsockets-dev "

libwebsockets_files = ""
libwebsockets_files += "${prefix}/bin/libwebsockets*"
libwebsockets_files += "${prefix}/lib/libwebsockets*.so.*"
libwebsockets_files += "${prefix}/share/libwebsockets-test-server/*"
MANIFESTFILES_${PN} = "libwebsockets.manifest"

libwebsockets-dev_files = ""
libwebsockets-dev_files += "${prefix}/include/libwebsockets.h"
libwebsockets-dev_files += "${prefix}/lib/libwebsockets.so"
libwebsockets-dev_files += "${prefix}/lib/pkgconfig/*"
MANIFESTFILES_${PN}-dev = "libwebsockets.manifest"

FILES_${PN} = "${libwebsockets_files}"
FILES_${PN}-dev = "${libwebsockets-dev_files}"

PKG_libwebsockets= "libwebsockets"
PKG_libwebsockets-dev= "libwebsockets-dev"

require libwebsockets-extraconf.inc

