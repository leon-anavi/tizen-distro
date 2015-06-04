DESCRIPTION = "A wav player library in Tizen C API"
HOMEPAGE = "http://nohomepage.org"
SECTION = "Multimedia/API"
LICENSE = "Apache-2.0"
PV = "0.1.0"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by capi-media-wav-player-dev
PROVIDES += "capi-media-wav-player-dev"


#PROVIDES by capi-media-wav-player


RDEPENDS = ""
#RDEPENDS of capi-media-wav-player-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "capi-media-wav-player"


DEPENDS = ""
#DEPENDS of capi-media-wav-player
DEPENDS += "libmm-sound"
inherit tizen_cmake
DEPENDS += "capi-media-sound-manager"
inherit pkgconfig
DEPENDS += "dlog"
DEPENDS += "capi-base-common"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/capi-media-wav-player.manifest .
 
 
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
 
 MAJORVER=`echo 0.1.0 | awk 'BEGIN {FS="."}{print $1}'`
 
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
         ${EXTRA_OECMAKE} . -DFULLVER=0.1.0 -DMAJORVER=${MAJORVER}
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
PACKAGES += " capi-media-wav-player-dev "
PACKAGES += " capi-media-wav-player "

capi-media-wav-player-dev_files = ""
capi-media-wav-player-dev_files += "${prefix}/include/media/*.h"
capi-media-wav-player-dev_files += "${prefix}/lib/pkgconfig/*.pc"
capi-media-wav-player-dev_files += "${prefix}/lib/libcapi-media-wav-player.so"
MANIFESTFILES_${PN}-dev = "capi-media-wav-player.manifest"

capi-media-wav-player_files = ""
capi-media-wav-player_files += "${prefix}/lib/libcapi-media-wav-player.so.*"
MANIFESTFILES_${PN} = "capi-media-wav-player.manifest"

FILES_${PN}-dev = "${capi-media-wav-player-dev_files}"
FILES_${PN} = "${capi-media-wav-player_files}"

PKG_capi-media-wav-player-dev= "capi-media-wav-player-dev"
PKG_capi-media-wav-player= "capi-media-wav-player"

require capi-media-wav-player-extraconf.inc

