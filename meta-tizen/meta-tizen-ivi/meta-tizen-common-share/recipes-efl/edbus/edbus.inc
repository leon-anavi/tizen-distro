DESCRIPTION = "EFL Wrapper for DBus"
HOMEPAGE = "http://www.enlightenment.org/"
SECTION = "Graphics & UI Framework/EFL"
LICENSE = "BSD-2-Clause"
PV = "1.7.8"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by edbus-dev
PROVIDES += "edbus-dev"


#PROVIDES by edbus


RDEPENDS = ""
#RDEPENDS of edbus-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "edbus"


DEPENDS = ""
#DEPENDS of edbus
DEPENDS += "evas"
DEPENDS += "ecore"
DEPENDS += "dbus"
inherit pkgconfig
DEPENDS += "eina"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q -n e_dbus-1.7.8
 cp ${S}/packaging/edbus.manifest .
 
 
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
  
  
  autotools_do_configure
  oe_runmake ${PARALLEL_MAKE}
  
  
  
}
EXTRA_OECONF += " --disable-static"

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
PACKAGES += " edbus-dev "
PACKAGES += " edbus "

edbus-dev_files = ""
edbus-dev_files += "${prefix}/include/e_dbus-1/*.h"
edbus-dev_files += "${prefix}/lib/*.so"
edbus-dev_files += "${prefix}/lib/pkgconfig/*.pc"
edbus-dev_files += "${prefix}/include/e_dbus-1/connman0_7x/E_Connman.h"
edbus-dev_files += "${prefix}/bin/e-notify-send"
MANIFESTFILES_${PN}-dev = "edbus.manifest"

edbus_files = ""
edbus_files += "${prefix}/bin/e_dbus_*"
edbus_files += "${prefix}/bin/e-notify-send"
edbus_files += "${prefix}/lib/libe*.so.*"
edbus_files += "${prefix}/share/e_dbus/logo.png"
MANIFESTFILES_${PN} = "edbus.manifest"

FILES_${PN}-dev = "${edbus-dev_files}"
FILES_${PN} = "${edbus_files}"

PKG_edbus-dev= "edbus-dev"
PKG_edbus= "edbus"

require edbus-extraconf.inc

