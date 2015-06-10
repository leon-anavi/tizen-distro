DESCRIPTION = "A System Settings library in Tizen Native API"
HOMEPAGE = "http://nohomepage.org"
SECTION = "System/API"
LICENSE = "Apache-2.0"
PV = "0.0.2"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by capi-system-system-settings-dev
PROVIDES += "capi-system-system-settings-dev"


#PROVIDES by capi-system-system-settings


RDEPENDS = ""
#RDEPENDS of capi-system-system-settings-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "capi-base-common"
RDEPENDS_${PN}-dev += "capi-system-system-settings"


DEPENDS = ""
#DEPENDS of capi-system-system-settings
inherit tizen_cmake
DEPENDS += "fontconfig"
DEPENDS += "tizen-platform-config"
inherit pkgconfig
DEPENDS += "dlog"
DEPENDS += "app-core"
DEPENDS += "capi-base-common"
DEPENDS += "libxml2"
DEPENDS += "elementary"
DEPENDS += "ecore"
DEPENDS += "glib-2.0"
DEPENDS += "vconf"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/capi-system-system-settings.manifest ${S}/packaging/capi-system-system-settings-devel.manifest .
 
 
 
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
 
 MAJORVER=`echo 0.0.2 | awk 'BEGIN {FS="."}{print $1}'`
 
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
         ${EXTRA_OECMAKE} . -DFULLVER=0.0.2 -DMAJORVER=${MAJORVER} \
         -DX11_SUPPORT=Off \
         -DWAYLAND_SUPPORT=On
 
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
PACKAGES += " capi-system-system-settings-dev "
PACKAGES += " capi-system-system-settings "

capi-system-system-settings-dev_files = ""
capi-system-system-settings-dev_files += "${prefix}/include/system/*.h"
capi-system-system-settings-dev_files += "${prefix}/lib/pkgconfig/*.pc"
capi-system-system-settings-dev_files += "${prefix}/lib/lib*.so"
MANIFESTFILES_${PN}-dev = "capi-system-system-settings-devel.manifest"

capi-system-system-settings_files = ""
capi-system-system-settings_files += "${prefix}/lib/lib*.so.*"
capi-system-system-settings_files += "/usr/bin/test_system_settings_gui"
MANIFESTFILES_${PN} = "capi-system-system-settings.manifest"

FILES_${PN}-dev = "${capi-system-system-settings-dev_files}"
FILES_${PN} = "${capi-system-system-settings_files}"

PKG_capi-system-system-settings-dev= "capi-system-system-settings-dev"
PKG_capi-system-system-settings= "capi-system-system-settings"

require capi-system-system-settings-extraconf.inc

