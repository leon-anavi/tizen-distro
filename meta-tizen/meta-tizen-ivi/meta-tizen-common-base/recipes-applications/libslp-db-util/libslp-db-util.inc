DESCRIPTION = "DB Utility"
HOMEPAGE = "http://nohomepage.org"
SECTION = "Application Framework/Database"
LICENSE = "Apache-2.0"
PV = "0.1.1"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by libslp-db-util-dev
PROVIDES += "libslp-db-util-dev"


#PROVIDES by libslp-db-util


RDEPENDS = ""
#RDEPENDS of libslp-db-util-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "libslp-db-util"


DEPENDS = ""
#DEPENDS of libslp-db-util
inherit tizen_cmake
inherit pkgconfig
DEPENDS += "dlog"
DEPENDS += "glib-2.0"
DEPENDS += "sqlite3"
DEPENDS += "icu"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/libslp-db-util.manifest ${S}/packaging/libslp-db-util-devel.manifest .
 
 
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
         ${EXTRA_OECMAKE} .
 make ${PARALLEL_MAKE}
 
 
 
}

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
PACKAGES += " libslp-db-util-dev "
PACKAGES += " libslp-db-util "

libslp-db-util-dev_files = ""
libslp-db-util-dev_files += "${prefix}/include/db-util"
libslp-db-util-dev_files += "${prefix}/include/db-util/*.h"
libslp-db-util-dev_files += "${prefix}/lib/pkgconfig/db-util.pc"
libslp-db-util-dev_files += "${prefix}/lib/libSLP-db-util.so"
MANIFESTFILES_${PN}-dev = "libslp-db-util-devel.manifest"
DIRFILES_${PN}-dev = ""
DIRFILES_${PN}-dev += "${prefix}/include/db-util"

libslp-db-util_files = ""
libslp-db-util_files += "${prefix}/lib/libSLP-db-util.so.0"
libslp-db-util_files += "${prefix}/lib/libSLP-db-util.so.0.1.0"
MANIFESTFILES_${PN} = "libslp-db-util.manifest"

FILES_${PN}-dev = "${libslp-db-util-dev_files}"
FILES_${PN} = "${libslp-db-util_files}"

PKG_libslp-db-util-dev= "libslp-db-util-dev"
PKG_libslp-db-util= "libslp-db-util"

require libslp-db-util-extraconf.inc

