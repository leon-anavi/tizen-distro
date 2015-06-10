DESCRIPTION = "Sensor framework client library"
HOMEPAGE = "http://nohomepage.org"
SECTION = "System/Sensor Framework"
LICENSE = "Apache-2.0"
PV = "0.5.27"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by sensor


#PROVIDES by sensor-dev
PROVIDES += "sensor-dev"


RDEPENDS = ""
#RDEPENDS of sensor-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "sensor"


DEPENDS = ""
#DEPENDS of sensor
DEPENDS += "libsf-common"
DEPENDS += "glib-2.0"
inherit tizen_cmake
DEPENDS += "vconf"
inherit pkgconfig

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q -n sensor-0.5.27
 cp ${S}/packaging/sensor.manifest ${S}/packaging/sensor-devel.manifest .
 
 
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
PACKAGES += " sensor "
PACKAGES += " sensor-dev "

sensor_files = ""
sensor_files += "${prefix}/lib/libsensor.so.*"
MANIFESTFILES_${PN} = "sensor.manifest"

sensor-dev_files = ""
sensor-dev_files += "${prefix}/include/sensor/*.h"
sensor-dev_files += "${prefix}/lib/libsensor.so"
sensor-dev_files += "${prefix}/lib/pkgconfig/sensor.pc"
MANIFESTFILES_${PN}-dev = "sensor-devel.manifest"

FILES_${PN} = "${sensor_files}"
FILES_${PN}-dev = "${sensor-dev_files}"

PKG_sensor= "sensor"
PKG_sensor-dev= "sensor-dev"

require sensor-extraconf.inc

