DESCRIPTION = "Common utilities for ico uifw"
HOMEPAGE = "http://nohomepage.org"
SECTION = "Automotive/Libraries"
LICENSE = "Apache-2.0"
PV = "0.9.07"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by ico-uxf-utilities


#PROVIDES by ico-uxf-utilities-dev
PROVIDES += "ico-uxf-utilities-dev"


RDEPENDS = ""
#RDEPENDS of ico-uxf-utilities (${PN})
RDEPENDS_${PN} += "coreutils"
RDEPENDS_${PN} += "automotive-message-broker"

#RDEPENDS of ico-uxf-utilities-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "ico-uxf-utilities"
RDEPENDS_${PN}-dev += "libwebsockets-dev"


DEPENDS = ""
#DEPENDS of ico-uxf-utilities
DEPENDS += "libwebsockets"
DEPENDS += "edbus"
inherit pkgconfig
DEPENDS += "dlog"
DEPENDS += "glib-2.0"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q -n ico-uxf-utilities-0.9.07
 
 
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
EXTRA_OECONF += ""

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
 
 # include
 mkdir -p ${D}${prefix}/include/ico-util/
 cp -f include/ico_uws.h ${D}${prefix}/include/ico-util/
 cp -f include/ico_log.h ${D}${prefix}/include/ico-util/
 cp -f include/ico_dbus_amb_efl.h ${D}${prefix}/include/ico-util/
 # log output
 mkdir -p ${D}/${localstatedir}/log/ico/
 chmod 0777 ${D}/${localstatedir}/log/ico/
 
 
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
PACKAGES += " ico-uxf-utilities "
PACKAGES += " ico-uxf-utilities-dev "

ico-uxf-utilities_files = ""
ico-uxf-utilities_files += "${prefix}/lib/libico-util*"
ico-uxf-utilities_files += "${localstatedir}/log/ico/"
MANIFESTFILES_${PN} = "ico-uxf-utilities.manifest"

ico-uxf-utilities-dev_files = ""
ico-uxf-utilities-dev_files += "${prefix}/include/ico-util/ico_uws.h"
ico-uxf-utilities-dev_files += "${prefix}/include/ico-util/ico_log.h"
ico-uxf-utilities-dev_files += "${prefix}/include/ico-util/ico_dbus_amb_efl.h"
ico-uxf-utilities-dev_files += "${prefix}/lib/libico-util*"
ico-uxf-utilities-dev_files += "${localstatedir}/log/ico/"
MANIFESTFILES_${PN}-dev = "ico-uxf-utilities.manifest"

FILES_${PN} = "${ico-uxf-utilities_files}"
FILES_${PN}-dev = "${ico-uxf-utilities-dev_files}"

PKG_ico-uxf-utilities= "ico-uxf-utilities"
PKG_ico-uxf-utilities-dev= "ico-uxf-utilities-dev"

require ico-uxf-utilities-extraconf.inc

