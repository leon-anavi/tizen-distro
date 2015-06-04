DESCRIPTION = "A Device library in TIZEN C API"
HOMEPAGE = "http://nohomepage.org"
SECTION = "System/API"
LICENSE = "Apache-2.0"
PV = "0.1.0"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by capi-system-device-dev
PROVIDES += "capi-system-device-dev"


#PROVIDES by capi-system-device


RDEPENDS = ""
#RDEPENDS of capi-system-device-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "capi-system-device"


DEPENDS = ""
#DEPENDS of capi-system-device
inherit tizen_cmake
inherit pkgconfig
DEPENDS += "dlog"
DEPENDS += "system-server"
DEPENDS += "capi-base-common"
DEPENDS += "vconf"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 
 
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
 
 cp ${S}/packaging/capi-system-device.manifest .
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
PACKAGES += " capi-system-device-dev "
PACKAGES += " capi-system-device "

capi-system-device-dev_files = ""
capi-system-device-dev_files += "${prefix}/include/system/device.h"
capi-system-device-dev_files += "${prefix}/lib/pkgconfig/*.pc"
capi-system-device-dev_files += "${prefix}/lib/libcapi-system-device.so"
MANIFESTFILES_${PN}-dev = "capi-system-device.manifest"

capi-system-device_files = ""
capi-system-device_files += "${prefix}/lib/libcapi-system-device.so.*"
MANIFESTFILES_${PN} = "capi-system-device.manifest"

FILES_${PN}-dev = "${capi-system-device-dev_files}"
FILES_${PN} = "${capi-system-device_files}"

PKG_capi-system-device-dev= "capi-system-device-dev"
PKG_capi-system-device= "capi-system-device"

require capi-system-device-extraconf.inc

