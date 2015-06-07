DESCRIPTION = "A Media content library in SLP C API"
HOMEPAGE = "http://nohomepage.org"
SECTION = "Multimedia/API"
LICENSE = "Apache-2.0"
PV = "0.2.59"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by capi-content-media-content


#PROVIDES by capi-content-media-content-dev
PROVIDES += "capi-content-media-content-dev"


RDEPENDS = ""
#RDEPENDS of capi-content-media-content-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "capi-content-media-content"


DEPENDS = ""
#DEPENDS of capi-content-media-content
DEPENDS += "libmedia-thumbnail"
inherit tizen_cmake
DEPENDS += "tizen-platform-config"
inherit pkgconfig
DEPENDS += "dlog"
DEPENDS += "media-server"
DEPENDS += "capi-base-common"
DEPENDS += "libmedia-service"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/capi-content-media-content.manifest .
 
 
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
 
 MAJORVER=`echo 0.2.59 | awk 'BEGIN {FS="."}{print $1}'`
 
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
         ${EXTRA_OECMAKE} . -DFULLVER=0.2.59 -DMAJORVER=${MAJORVER}
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
PACKAGES += " capi-content-media-content "
PACKAGES += " capi-content-media-content-dev "

capi-content-media-content_files = ""
capi-content-media-content_files += "${prefix}/lib/libcapi-content-media-content.so.*"
MANIFESTFILES_${PN} = "capi-content-media-content.manifest"

capi-content-media-content-dev_files = ""
capi-content-media-content-dev_files += "${prefix}/include/media-content/*.h"
capi-content-media-content-dev_files += "${prefix}/lib/pkgconfig/*.pc"
capi-content-media-content-dev_files += "${prefix}/lib/libcapi-content-media-content.so"
MANIFESTFILES_${PN}-dev = "capi-content-media-content.manifest"

FILES_${PN} = "${capi-content-media-content_files}"
FILES_${PN}-dev = "${capi-content-media-content-dev_files}"

PKG_capi-content-media-content= "capi-content-media-content"
PKG_capi-content-media-content-dev= "capi-content-media-content-dev"

require capi-content-media-content-extraconf.inc

