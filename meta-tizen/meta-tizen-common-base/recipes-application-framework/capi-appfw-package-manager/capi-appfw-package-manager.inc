DESCRIPTION = "Package Manager API"
HOMEPAGE = "http://nohomepage.org"
SECTION = "System/API"
LICENSE = "Apache-2.0"
PV = "0.0.30"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by capi-appfw-package-manager-dev
PROVIDES += "capi-appfw-package-manager-dev"


#PROVIDES by capi-appfw-package-manager


RDEPENDS = ""
#RDEPENDS of capi-appfw-package-manager-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "capi-appfw-package-manager"


DEPENDS = ""
#DEPENDS of capi-appfw-package-manager
inherit tizen_cmake
DEPENDS += "pkgmgr"
DEPENDS += "tizen-platform-config"
inherit pkgconfig
DEPENDS += "pkgmgr-info"
DEPENDS += "aul"
DEPENDS += "ail"
DEPENDS += "dlog"
DEPENDS += "vconf"
DEPENDS += "capi-base-common"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/capi-appfw-package-manager.manifest .
 
 
 
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
 
 MAJORVER=`echo 0.0.30 | awk 'BEGIN {FS="."}{print $1}'`
 
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
         ${EXTRA_OECMAKE} . -DFULLVER=0.0.30 -DMAJORVER=${MAJORVER}
 
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
PACKAGES += " capi-appfw-package-manager-dev "
PACKAGES += " capi-appfw-package-manager "

capi-appfw-package-manager-dev_files = ""
capi-appfw-package-manager-dev_files += "${prefix}/include/appfw/package_manager.h"
capi-appfw-package-manager-dev_files += "${prefix}/include/appfw/package_info.h"
capi-appfw-package-manager-dev_files += "${prefix}/lib/libcapi-appfw-package-manager.so"
capi-appfw-package-manager-dev_files += "${prefix}/lib/pkgconfig/*.pc"
MANIFESTFILES_${PN}-dev = "capi-appfw-package-manager.manifest"

capi-appfw-package-manager_files = ""
capi-appfw-package-manager_files += "${prefix}/lib/libcapi-appfw-package-manager.so.*"
capi-appfw-package-manager_files += "${prefix}/bin/pkgmgr_tool"
MANIFESTFILES_${PN} = "capi-appfw-package-manager.manifest"

FILES_${PN}-dev = "${capi-appfw-package-manager-dev_files}"
FILES_${PN} = "${capi-appfw-package-manager_files}"

PKG_capi-appfw-package-manager-dev= "capi-appfw-package-manager-dev"
PKG_capi-appfw-package-manager= "capi-appfw-package-manager"

require capi-appfw-package-manager-extraconf.inc

