DESCRIPTION = "A Sensor library in TIZEN C API"
HOMEPAGE = "http://nohomepage.org"
SECTION = "System/API"
LICENSE = "Apache 2.0"
PV = "0.1.0"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by capi-system-sensor-dev
PROVIDES += "capi-system-sensor-dev"


#PROVIDES by capi-system-sensor


RDEPENDS = ""
#RDEPENDS of capi-system-sensor-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "capi-system-sensor"

#RDEPENDS of capi-system-sensor (${PN})
RDEPENDS_${PN} += "glibc"


DEPENDS = ""
#DEPENDS of capi-system-sensor
DEPENDS += "sensor"
inherit tizen_cmake
inherit pkgconfig
DEPENDS += "dlog"
DEPENDS += "capi-base-common"
DEPENDS += "libsf-common"

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
 
 cp ${S}/packaging/capi-system-sensor.manifest .
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
PACKAGES += " capi-system-sensor-dev "
PACKAGES += " capi-system-sensor "

capi-system-sensor-dev_files = ""
capi-system-sensor-dev_files += "${prefix}/lib/libcapi-system-sensor.so"
capi-system-sensor-dev_files += "${prefix}/lib/pkgconfig/*.pc"
capi-system-sensor-dev_files += "${prefix}/include/sensor/*.h"
MANIFESTFILES_${PN}-dev = "capi-system-sensor.manifest"

capi-system-sensor_files = ""
capi-system-sensor_files += "${prefix}/lib/libcapi-system-sensor.so.*"
MANIFESTFILES_${PN} = "capi-system-sensor.manifest"

FILES_${PN}-dev = "${capi-system-sensor-dev_files}"
FILES_${PN} = "${capi-system-sensor_files}"

PKG_capi-system-sensor-dev= "capi-system-sensor-dev"
PKG_capi-system-sensor= "capi-system-sensor"

require capi-system-sensor-extraconf.inc

