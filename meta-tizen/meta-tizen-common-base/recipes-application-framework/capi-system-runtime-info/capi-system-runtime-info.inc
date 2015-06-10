DESCRIPTION = "A Runtime Information library in Core API"
HOMEPAGE = "http://nohomepage.org"
SECTION = "System/API"
LICENSE = "Apache-2.0"
PV = "0.0.3"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by capi-system-runtime-info-dev
PROVIDES += "capi-system-runtime-info-dev"


#PROVIDES by capi-system-runtime-info


RDEPENDS = ""
#RDEPENDS of capi-system-runtime-info-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "capi-base-common"
RDEPENDS_${PN}-dev += "capi-system-runtime-info"

#RDEPENDS of capi-system-runtime-info (${PN})
RDEPENDS_${PN} += "glibc"


DEPENDS = ""
#DEPENDS of capi-system-runtime-info
DEPENDS += "capi-base-common"
inherit tizen_cmake
inherit pkgconfig
DEPENDS += "dlog"
DEPENDS += "vconf"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/capi-system-runtime-info.manifest .
 
 
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
 
 MAJORVER=`echo 0.0.3 | awk 'BEGIN {FS="."}{print $1}'`
 
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
         ${EXTRA_OECMAKE} . -DFULLVER=0.0.3 -DMAJORVER=${MAJORVER}
 
 
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
PACKAGES += " capi-system-runtime-info-dev "
PACKAGES += " capi-system-runtime-info "

capi-system-runtime-info-dev_files = ""
capi-system-runtime-info-dev_files += "${prefix}/include/system/*.h"
capi-system-runtime-info-dev_files += "${prefix}/lib/pkgconfig/*.pc"
capi-system-runtime-info-dev_files += "${prefix}/lib/lib*.so"

capi-system-runtime-info_files = ""
capi-system-runtime-info_files += "${prefix}/lib/lib*.so.*"
MANIFESTFILES_${PN} = "capi-system-runtime-info.manifest"

FILES_${PN}-dev = "${capi-system-runtime-info-dev_files}"
FILES_${PN} = "${capi-system-runtime-info_files}"

PKG_capi-system-runtime-info-dev= "capi-system-runtime-info-dev"
PKG_capi-system-runtime-info= "capi-system-runtime-info"

require capi-system-runtime-info-extraconf.inc

