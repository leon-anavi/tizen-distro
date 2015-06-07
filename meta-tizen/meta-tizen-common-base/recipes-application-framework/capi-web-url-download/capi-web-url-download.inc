DESCRIPTION = "CAPI for content download with web url"
HOMEPAGE = "http://nohomepage.org"
SECTION = "Development/Libraries"
LICENSE = "Apache-2.0"
PV = "1.1.1"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by capi-web-url-download


#PROVIDES by capi-web-url-download-dev
PROVIDES += "capi-web-url-download-dev"


RDEPENDS = ""
#RDEPENDS of capi-web-url-download-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "capi-web-url-download"


DEPENDS = ""
#DEPENDS of capi-web-url-download
inherit tizen_cmake
inherit pkgconfig
DEPENDS += "bundle"
DEPENDS += "download-provider"
DEPENDS += "dlog"
DEPENDS += "capi-base-common"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 
 
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
 
 rm -rf ${D}
 
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
PACKAGES += " capi-web-url-download "
PACKAGES += " capi-web-url-download-dev "

capi-web-url-download_files = ""
capi-web-url-download_files += "${prefix}/lib/libcapi-web-url-download.so.*"
capi-web-url-download_files += "/usr/share/license/capi-web-url-download"
MANIFESTFILES_${PN} = "capi-web-url-download.manifest"

capi-web-url-download-dev_files = ""
capi-web-url-download-dev_files += "${prefix}/lib/libcapi-web-url-download.so"
capi-web-url-download-dev_files += "${prefix}/lib/pkgconfig/capi-web-url-download.pc"
capi-web-url-download-dev_files += "${prefix}/include/web/download.h"
capi-web-url-download-dev_files += "${prefix}/include/web/download_doc.h"
MANIFESTFILES_${PN}-dev = "capi-web-url-download.manifest"

FILES_${PN} = "${capi-web-url-download_files}"
FILES_${PN}-dev = "${capi-web-url-download-dev_files}"

PKG_capi-web-url-download= "capi-web-url-download"
PKG_capi-web-url-download-dev= "capi-web-url-download-dev"

require capi-web-url-download-extraconf.inc

