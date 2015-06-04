DESCRIPTION = "Sound Manager library"
HOMEPAGE = "http://nohomepage.org"
SECTION = "Multimedia/API"
LICENSE = "Apache-2.0"
PV = "0.1.1"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by capi-media-sound-manager-dev
PROVIDES += "capi-media-sound-manager-dev"


#PROVIDES by capi-media-sound-manager


RDEPENDS = ""
#RDEPENDS of capi-media-sound-manager-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "capi-media-sound-manager"


DEPENDS = ""
#DEPENDS of capi-media-sound-manager
DEPENDS += "libmm-sound"
inherit tizen_cmake
inherit pkgconfig
DEPENDS += "dlog"
DEPENDS += "capi-base-common"
DEPENDS += "libmm-session"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/capi-media-sound-manager.manifest .
 
 
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
 
 MAJORVER=`echo 0.1.1 | awk 'BEGIN {FS="."}{print $1}'`
 
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
         ${EXTRA_OECMAKE} . -DFULLVER=0.1.1 -DMAJORVER=${MAJORVER}
 oe_runmake -j16
 
 
 
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
PACKAGES += " capi-media-sound-manager-dev "
PACKAGES += " capi-media-sound-manager "

capi-media-sound-manager-dev_files = ""
capi-media-sound-manager-dev_files += "${prefix}/include/media/sound_manager.h"
capi-media-sound-manager-dev_files += "${prefix}/lib/pkgconfig/*.pc"
capi-media-sound-manager-dev_files += "${prefix}/lib/libcapi-media-sound-manager.so"
MANIFESTFILES_${PN}-dev = "capi-media-sound-manager.manifest"

capi-media-sound-manager_files = ""
capi-media-sound-manager_files += "${prefix}/lib/libcapi-media-sound-manager.so.*"
MANIFESTFILES_${PN} = "capi-media-sound-manager.manifest"

FILES_${PN}-dev = "${capi-media-sound-manager-dev_files}"
FILES_${PN} = "${capi-media-sound-manager_files}"

PKG_capi-media-sound-manager-dev= "capi-media-sound-manager-dev"
PKG_capi-media-sound-manager= "capi-media-sound-manager"

require capi-media-sound-manager-extraconf.inc

