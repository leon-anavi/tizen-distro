DESCRIPTION = "A System Information library in SLP C API"
HOMEPAGE = "http://nohomepage.org"
SECTION = "System/API"
LICENSE = "Apache-2.0"
PV = "0.2.0"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by capi-system-info-dev
PROVIDES += "capi-system-info-dev"


#PROVIDES by capi-system-info


RDEPENDS = ""
#RDEPENDS of capi-system-info-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "capi-system-info"


DEPENDS = ""
#DEPENDS of capi-system-info
inherit tizen_cmake
DEPENDS += "libxml2"
inherit pkgconfig
DEPENDS += "iniparser"
DEPENDS += "dlog"
DEPENDS += "ecore"
DEPENDS += "vconf"
DEPENDS += "capi-base-common"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/capi-system-info.manifest .
 
 
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
 
 MAJORVER=`echo 0.2.0 | awk 'BEGIN {FS="."}{print $1}'`
 
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
         ${EXTRA_OECMAKE} . -DFULLVER=0.2.0 -DMAJORVER=${MAJORVER} -DENABLE_WAYLAND=TRUE
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
 mkdir -p ${D}${sysconfdir}
 cp -f script/make_info_file.sh ${D}${sysconfdir}/make_info_file.sh
 
 
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
PACKAGES += " capi-system-info-dev "
PACKAGES += " capi-system-info "

capi-system-info-dev_files = ""
capi-system-info-dev_files += "${prefix}/include/system/system_info.h"
capi-system-info-dev_files += "${prefix}/lib/pkgconfig/*.pc"
capi-system-info-dev_files += "${prefix}/lib/libcapi-system-info.so"
MANIFESTFILES_${PN}-dev = "capi-system-info.manifest"

capi-system-info_files = ""
capi-system-info_files += "${prefix}/lib/libcapi-system-info.so.*"
capi-system-info_files += "${sysconfdir}/make_info_file.sh"
MANIFESTFILES_${PN} = "capi-system-info.manifest"

FILES_${PN}-dev = "${capi-system-info-dev_files}"
FILES_${PN} = "${capi-system-info_files}"

PKG_capi-system-info-dev= "capi-system-info-dev"
PKG_capi-system-info= "capi-system-info"

require capi-system-info-extraconf.inc

