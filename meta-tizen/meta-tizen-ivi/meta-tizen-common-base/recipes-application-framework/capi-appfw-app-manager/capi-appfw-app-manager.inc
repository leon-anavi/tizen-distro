DESCRIPTION = "Application Manager API"
HOMEPAGE = "http://nohomepage.org"
SECTION = "Application Framework/API"
LICENSE = "Apache-2.0"
PV = "0.1.0"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by capi-appfw-app-manager


#PROVIDES by capi-appfw-app-manager-dev
PROVIDES += "capi-appfw-app-manager-dev"


RDEPENDS = ""
#RDEPENDS of capi-appfw-app-manager-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "capi-appfw-app-manager"


DEPENDS = ""
#DEPENDS of capi-appfw-app-manager
inherit tizen_cmake
DEPENDS += "pkgmgr"
DEPENDS += "aul"
DEPENDS += "dlog"
inherit pkgconfig
DEPENDS += "ail"
DEPENDS += "pkgmgr-info"
DEPENDS += "glib-2.0"
DEPENDS += "vconf"
DEPENDS += "capi-base-common"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/capi-appfw-app-manager.manifest .
 
 
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
PACKAGES += " capi-appfw-app-manager "
PACKAGES += " capi-appfw-app-manager-dev "

capi-appfw-app-manager_files = ""
capi-appfw-app-manager_files += "${prefix}/lib/libcapi-appfw-app-manager.so.*"
MANIFESTFILES_${PN} = "capi-appfw-app-manager.manifest"

capi-appfw-app-manager-dev_files = ""
capi-appfw-app-manager-dev_files += "${prefix}/include/appfw/*.h"
capi-appfw-app-manager-dev_files += "${prefix}/lib/libcapi-appfw-app-manager.so"
capi-appfw-app-manager-dev_files += "${prefix}/lib/pkgconfig/*.pc"
MANIFESTFILES_${PN}-dev = "capi-appfw-app-manager.manifest"

FILES_${PN} = "${capi-appfw-app-manager_files}"
FILES_${PN}-dev = "${capi-appfw-app-manager-dev_files}"

PKG_capi-appfw-app-manager= "capi-appfw-app-manager"
PKG_capi-appfw-app-manager-dev= "capi-appfw-app-manager-dev"

require capi-appfw-app-manager-extraconf.inc

