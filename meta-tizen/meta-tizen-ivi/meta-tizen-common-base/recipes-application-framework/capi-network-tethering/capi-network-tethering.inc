DESCRIPTION = "Tethering Framework"
HOMEPAGE = "http://nohomepage.org"
SECTION = "Connectivity/API"
LICENSE = "Apache-2.0"
PV = "0.0.16"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by capi-network-tethering-dev
PROVIDES += "capi-network-tethering-dev"


#PROVIDES by capi-network-tethering


RDEPENDS = ""
#RDEPENDS of capi-network-tethering-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "capi-network-tethering"


DEPENDS = ""
#DEPENDS of capi-network-tethering
inherit tizen_cmake
inherit pkgconfig
DEPENDS += "dlog"
DEPENDS += "glib-2.0"
DEPENDS += "capi-base-common"
DEPENDS += "vconf"
DEPENDS += "dbus-glib"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/capi-network-tethering.manifest .
 
 
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
         ${EXTRA_OECMAKE} . -DARCH=i586
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
 mkdir -p ${D}/usr/share/license
 cp LICENSE.APLv2.0 ${D}/usr/share/license/capi-network-tethering
 
 
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
PACKAGES += " capi-network-tethering-dev "
PACKAGES += " capi-network-tethering "

capi-network-tethering-dev_files = ""
capi-network-tethering-dev_files += "${prefix}/include/network/*.h"
capi-network-tethering-dev_files += "${prefix}/lib/pkgconfig/*.pc"
capi-network-tethering-dev_files += "${prefix}/lib/*.so"
MANIFESTFILES_${PN}-dev = "capi-network-tethering.manifest"

capi-network-tethering_files = ""
capi-network-tethering_files += "${prefix}/lib/*.so.*"
capi-network-tethering_files += "/usr/share/license/capi-network-tethering"
capi-network-tethering_files += "/etc/config/connectivity/sysinfo-tethering.xml"
MANIFESTFILES_${PN} = "capi-network-tethering.manifest"

FILES_${PN}-dev = "${capi-network-tethering-dev_files}"
FILES_${PN} = "${capi-network-tethering_files}"

PKG_capi-network-tethering-dev= "capi-network-tethering-dev"
PKG_capi-network-tethering= "capi-network-tethering"

require capi-network-tethering-extraconf.inc

