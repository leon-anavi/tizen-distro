DESCRIPTION = "WBXML parser and compiler library"
HOMEPAGE = "http://libwbxml.opensync.org/"
SECTION = "System/Libraries"
LICENSE = "LGPL-2.1+"
PV = "0.11.2"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by libwbxml2


#PROVIDES by wbxml2-tools
PROVIDES += "wbxml2-tools"


#PROVIDES by libwbxml2-dev
PROVIDES += "libwbxml2-dev"


RDEPENDS = ""
#RDEPENDS of wbxml2-tools (wbxml2-tools)
RDEPENDS_wbxml2-tools += "libwbxml2"
RDEPENDS_wbxml2-tools += "libxml2"

#RDEPENDS of libwbxml2-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "libwbxml2"
RDEPENDS_${PN}-dev += "libxml2"
RDEPENDS_${PN}-dev += "glibc"
RDEPENDS_${PN}-dev += "expat"


DEPENDS = ""
#DEPENDS of libwbxml2
DEPENDS += "expat"
inherit tizen_cmake
DEPENDS += "libxml2"
DEPENDS += "zlib"
inherit pkgconfig
DEPENDS += "popt"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q -n libwbxml-0.11.2
 cp ${S}/packaging/libwbxml2.manifest .
 
 
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
 
 mkdir build
 CURDIR=$(pwd)
 cd build
 CFLAGS="$CFLAGS" \
 CXXFLAGS="$CFLAGS" \
 
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
         ${EXTRA_OECMAKE} \
         -DCMAKE_BUILD_TYPE=None \
         -DENABLE_INSTALL_DOC:BOOL=OFF \
          ${WORKDIR}/libwbxml-0.11.2
 make ${PARALLEL_MAKE} VERBOSE=1
 cd ${CURDIR}
 
 
 
}

do_install() {
 export RPM_BUILD_ROOT=${D}
 cd ${S}
 LANG=C
 export LANG
 unset DISPLAY
 rm -rf ${D}
 mkdir -p ${D}
 
 CURDIR=$(pwd)
 cd build
 
   oe_runmake \
         DESTDIR=${D} \
         INSTALL_ROOT=${D} \
         BINDIR=${prefix}/bin \
   install  
   rm -f ${D}${infodir}/dir 
   find ${D} -regex ".*\.la$" | xargs rm -f -- 
   find ${D} -regex ".*\.a$" | xargs rm -f --
 cd ${CURDIR}
 
 
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
PACKAGES += " libwbxml2 "
PACKAGES += " wbxml2-tools "
PACKAGES += " libwbxml2-dev "

libwbxml2_files = ""
libwbxml2_files += "${prefix}/lib/libwbxml2.so.1*"
MANIFESTFILES_${PN} = "libwbxml2.manifest"

wbxml2-tools_files = ""
wbxml2-tools_files += "${prefix}/bin/wbxml2xml"
wbxml2-tools_files += "${prefix}/bin/xml2wbxml"
MANIFESTFILES_wbxml2-tools = "libwbxml2.manifest"

libwbxml2-dev_files = ""
libwbxml2-dev_files += "${prefix}/lib/pkgconfig/libwbxml2.pc"
libwbxml2-dev_files += "${prefix}/lib/libwbxml2.so"
libwbxml2-dev_files += "${prefix}/include/libwbxml-1.0/wbxml"
libwbxml2-dev_files += "${prefix}/share/cmake/Modules/FindLibWbxml2.cmake"
libwbxml2-dev_files += "${prefix}/include/wbxml_config.h"
MANIFESTFILES_${PN}-dev = "libwbxml2.manifest"

FILES_${PN} = "${libwbxml2_files}"
FILES_wbxml2-tools = "${wbxml2-tools_files}"
FILES_${PN}-dev = "${libwbxml2-dev_files}"

PKG_libwbxml2= "libwbxml2"
PKG_wbxml2-tools= "wbxml2-tools"
PKG_libwbxml2-dev= "libwbxml2-dev"

require libwbxml2-extraconf.inc

