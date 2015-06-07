DESCRIPTION = "Wifi Direct Library"
HOMEPAGE = "http://nohomepage.org"
SECTION = "Network & Connectivity/Wireless"
LICENSE = "Apache-2.0"
PV = "1.0.9"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by libwifi-direct


#PROVIDES by libwifi-direct-dev
PROVIDES += "libwifi-direct-dev"


RDEPENDS = ""
#RDEPENDS of libwifi-direct-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "libwifi-direct"


DEPENDS = ""
#DEPENDS of libwifi-direct
inherit tizen_cmake
inherit pkgconfig
#Replace "DEPENDS" on gettext by "inherit gettext"
inherit gettext
DEPENDS += "dlog"
DEPENDS += "vconf"
DEPENDS += "dbus-glib"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/libwifi-direct.manifest .
 

 export ARCH=i586
 
 
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
 
 mkdir -p ${D}/usr/share/license
 cp ${WORKDIR}/git/LICENSE.APLv2 ${D}/usr/share/license/libwifi-direct
 
 
 
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
PACKAGES += " libwifi-direct "
PACKAGES += " libwifi-direct-dev "

libwifi-direct_files = ""
libwifi-direct_files += "${prefix}/lib/libwifi-direct.so"
libwifi-direct_files += "${prefix}/lib/libwifi-direct.so.0"
libwifi-direct_files += "${prefix}/lib/libwifi-direct.so.0.0"
libwifi-direct_files += "/usr/share/license/libwifi-direct"
MANIFESTFILES_${PN} = "libwifi-direct.manifest"

libwifi-direct-dev_files = ""
libwifi-direct-dev_files += "${prefix}/lib/pkgconfig/wifi-direct.pc"
libwifi-direct-dev_files += "${prefix}/include/wifi-direct/wifi-direct.h"
libwifi-direct-dev_files += "${prefix}/include/wifi-direct/wifi-direct-internal.h"
MANIFESTFILES_${PN}-dev = "libwifi-direct.manifest"

FILES_${PN} = "${libwifi-direct_files}"
FILES_${PN}-dev = "${libwifi-direct-dev_files}"

PKG_libwifi-direct= "libwifi-direct"
PKG_libwifi-direct-dev= "libwifi-direct-dev"

require libwifi-direct-extraconf.inc

