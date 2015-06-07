DESCRIPTION = "An Application library in SLP C API"
HOMEPAGE = "http://nohomepage.org"
SECTION = "System/API"
LICENSE = "Apache-2.0"
PV = "0.1.0"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by capi-appfw-application-dev
PROVIDES += "capi-appfw-application-dev"


#PROVIDES by capi-appfw-application


RDEPENDS = ""
#RDEPENDS of capi-appfw-application-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "capi-appfw-application"


DEPENDS = ""
#DEPENDS of capi-appfw-application
DEPENDS += "sqlite3"
inherit tizen_cmake
DEPENDS += "notification"
DEPENDS += "tizen-platform-config"
DEPENDS += "app-svc"
DEPENDS += "aul"
DEPENDS += "bundle"
inherit pkgconfig
DEPENDS += "ail"
DEPENDS += "alarm-manager"
DEPENDS += "dlog"
DEPENDS += "elementary"
DEPENDS += "app-core"
DEPENDS += "capi-base-common"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/capi-appfw-application.manifest .
 
 
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
 mkdir -p ${D}${prefix}/share/license
 cp LICENSE ${D}${prefix}/share/license/capi-appfw-application
 
 
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
PACKAGES += " capi-appfw-application-dev "
PACKAGES += " capi-appfw-application "

capi-appfw-application-dev_files = ""
capi-appfw-application-dev_files += "${prefix}/include/appfw/*.h"
capi-appfw-application-dev_files += "${prefix}/lib/pkgconfig/*.pc"
capi-appfw-application-dev_files += "${prefix}/lib/libcapi-appfw-application.so"
MANIFESTFILES_${PN}-dev = "capi-appfw-application.manifest"

capi-appfw-application_files = ""
capi-appfw-application_files += "${prefix}/lib/libcapi-appfw-application.so.*"
capi-appfw-application_files += "${prefix}/share/license/capi-appfw-application"
MANIFESTFILES_${PN} = "capi-appfw-application.manifest"

FILES_${PN}-dev = "${capi-appfw-application-dev_files}"
FILES_${PN} = "${capi-appfw-application_files}"

PKG_capi-appfw-application-dev= "capi-appfw-application-dev"
PKG_capi-appfw-application= "capi-appfw-application"

require capi-appfw-application-extraconf.inc

