DESCRIPTION = "String key-val dictionary ADT"
HOMEPAGE = "http://nohomepage.org"
SECTION = "System/Libraries"
LICENSE = "Apache-2.0"
PV = "0.1.31"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by bundle-dev
PROVIDES += "bundle-dev"


#PROVIDES by bundle


RDEPENDS = ""
#RDEPENDS of bundle-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "bundle"


DEPENDS = ""
#DEPENDS of bundle
inherit tizen_cmake
inherit pkgconfig
DEPENDS += "dlog"
DEPENDS += "glib-2.0"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q -n bundle-0.1.31
 cp ${S}/packaging/bundle.manifest .
 
 
 
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
 
 mkdir -p ${D}/usr/share/license
 
 
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
PACKAGES += " bundle-dev "
PACKAGES += " bundle "

bundle-dev_files = ""
bundle-dev_files += "${prefix}/include/bundle.h"
bundle-dev_files += "${prefix}/include/SLP_bundle_PG.h"
bundle-dev_files += "${prefix}/lib/pkgconfig/bundle.pc"
bundle-dev_files += "${prefix}/lib/libbundle.so"
MANIFESTFILES_${PN}-dev = "bundle.manifest"

bundle_files = ""
bundle_files += "${prefix}/lib/libbundle.so.*"
MANIFESTFILES_${PN} = "bundle.manifest"

FILES_${PN}-dev = "${bundle-dev_files}"
FILES_${PN} = "${bundle_files}"

PKG_bundle-dev= "bundle-dev"
PKG_bundle= "bundle"

require bundle-extraconf.inc

