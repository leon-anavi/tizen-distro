DESCRIPTION = "Logging service"
HOMEPAGE = "http://nohomepage.org"
SECTION = "System/Libraries"
LICENSE = "Apache-2.0"
PV = "0.4.1"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by libdlog
PROVIDES += "libdlog"


#PROVIDES by dlogutil
PROVIDES += "dlogutil"


#PROVIDES by dlog


#PROVIDES by libdlog-dev
PROVIDES += "libdlog-dev"


RDEPENDS = ""
#RDEPENDS of dlogutil (${PN}util)
RDEPENDS_${PN}util += "libdlog"

#RDEPENDS of libdlog-dev (lib${PN}-dev)
RDEPENDS_lib${PN}-dev += "libdlog"


DEPENDS = ""
#DEPENDS of dlog
DEPENDS += "systemd"
DEPENDS += "tizen-platform-config"
inherit pkgconfig

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/dlog.manifest .
 
 
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
 mkdir -p ${D}${sysconfdir}/dlog
 cp platformlog.conf ${D}${sysconfdir}/dlog/platformlog.conf
 cp dlogctrl ${D}${prefix}/bin/dlogctrl
 
 
}

pkg_postinst_libdlog() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_libdlog() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " libdlog "
PACKAGES += " dlogutil "
PACKAGES += " libdlog-dev "

libdlog_files = ""
libdlog_files += "${sysconfdir}/dlog/platformlog.conf"
libdlog_files += "${prefix}/lib/libdlog.so.*"
CONFFILES_lib${PN} = ""
CONFFILES_lib${PN} += "${sysconfdir}/dlog/platformlog.conf"
MANIFESTFILES_lib${PN} = "dlog.manifest"

dlogutil_files = ""
dlogutil_files += "${prefix}/bin/dlogctrl"
MANIFESTFILES_${PN}util = "dlog.manifest"

libdlog-dev_files = ""
libdlog-dev_files += "${prefix}/include/dlog/dlog.h"
libdlog-dev_files += "${prefix}/lib/pkgconfig/dlog.pc"
libdlog-dev_files += "${prefix}/lib/libdlog.so"
MANIFESTFILES_lib${PN}-dev = "dlog.manifest"

FILES_lib${PN} = "${libdlog_files}"
FILES_${PN}util = "${dlogutil_files}"
FILES_lib${PN}-dev = "${libdlog-dev_files}"

PKG_libdlog= "libdlog"
PKG_dlogutil= "dlogutil"
PKG_libdlog-dev= "libdlog-dev"

require dlog-extraconf.inc

