DESCRIPTION = "Location Based Service"
HOMEPAGE = "http://nohomepage.org"
SECTION = "Location/Libraries"
LICENSE = "Apache-2.0"
PV = "0.5.3"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by libslp-location-dev
PROVIDES += "libslp-location-dev"


#PROVIDES by libslp-location


RDEPENDS = ""
#RDEPENDS of libslp-location-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "libslp-location"

#RDEPENDS of libslp-location (${PN})
RDEPENDS_${PN} += "glibc"
RDEPENDS_${PN} += "vconf"


DEPENDS = ""
#DEPENDS of libslp-location
inherit pkgconfig
DEPENDS += "dlog"
DEPENDS += "glib-2.0"
DEPENDS += "json-glib"
DEPENDS += "vconf"
DEPENDS += "dbus-glib"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q -n libslp-location-0.5.3
 cp ${S}/packaging/libslp-location.manifest .
 
 
 
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
  
  ./autogen.sh
  
  autotools_do_configure
  oe_runmake -j16
  
  
  
  
}
EXTRA_OECONF += " --enable-dlog --enable-debug"

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
    vconftool set -t int db/location/last/gps/Timestamp "0" -f
    vconftool set -t double db/location/last/gps/Latitude "0.0" -f
    vconftool set -t double db/location/last/gps/Longitude "0.0" -f
    vconftool set -t double db/location/last/gps/Altitude "0.0" -f
    vconftool set -t double db/location/last/gps/HorAccuracy "0.0" -f
    vconftool set -t double db/location/last/gps/VerAccuracy "0.0" -f
    vconftool set -t double db/location/last/gps/Speed "0.0" -f
    vconftool set -t double db/location/last/gps/Direction "0.0" -f
    vconftool set -t int db/location/last/wps/Timestamp "0" -f
    vconftool set -t double db/location/last/wps/Latitude "0.0" -f
    vconftool set -t double db/location/last/wps/Longitude "0.0" -f
    vconftool set -t double db/location/last/wps/Altitude "0.0" -f
    vconftool set -t double db/location/last/wps/HorAccuracy "0.0" -f
    vconftool set -t double db/location/last/wps/Speed "0.0" -f
    vconftool set -t double db/location/last/wps/Direction "0.0" -f
    vconftool set -t int db/location/setting/GpsEnabled "0" -g 6514 -f
    vconftool set -t int db/location/setting/AgpsEnabled "0" -g 6514 -f
    vconftool set -t int db/location/setting/NetworkEnabled "0" -g 6514 -f

}

pkg_postrm_${PN}() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " libslp-location-dev "
PACKAGES += " libslp-location "

libslp-location-dev_files = ""
libslp-location-dev_files += "${prefix}/include/location/*.h"
libslp-location-dev_files += "${prefix}/lib/pkgconfig/*.pc"
MANIFESTFILES_${PN}-dev = "libslp-location.manifest"

libslp-location_files = ""
libslp-location_files += "${prefix}/lib/lib*.so*"
MANIFESTFILES_${PN} = "libslp-location.manifest"

FILES_${PN}-dev = "${libslp-location-dev_files}"
FILES_${PN} = "${libslp-location_files}"

PKG_libslp-location-dev= "libslp-location-dev"
PKG_libslp-location= "libslp-location"

require libslp-location-extraconf.inc

