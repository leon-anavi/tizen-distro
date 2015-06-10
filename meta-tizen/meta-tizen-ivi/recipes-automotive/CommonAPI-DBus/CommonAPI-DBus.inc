DESCRIPTION = "GENIVI IPC Common API C++ DBus"
HOMEPAGE = "http://nohomepage.org"
SECTION = "Automotive/GENIVI"
LICENSE = "MPL-2.0"
PV = "2.1.6"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by libCommonAPI-DBus
PROVIDES += "libCommonAPI-DBus"


#PROVIDES by CommonAPI-DBus


#PROVIDES by CommonAPI-DBus-dev
PROVIDES += "CommonAPI-DBus-dev"


RDEPENDS = ""
#RDEPENDS of CommonAPI-DBus (${PN})
RDEPENDS_${PN} += "glibc"

#RDEPENDS of CommonAPI-DBus-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "libCommonAPI-DBus"


DEPENDS = ""
#DEPENDS of CommonAPI-DBus
DEPENDS += "CommonAPI"
DEPENDS += "dbus"
inherit pkgconfig
DEPENDS += "glib-2.0"

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
  
  autoreconf -i
  
  autotools_do_configure
  oe_runmake ${PARALLEL_MAKE}
  
  
  
}
EXTRA_OECONF += " "

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

pkg_postinst_libCommonAPI-DBus() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_libCommonAPI-DBus() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " libCommonAPI-DBus "
PACKAGES += " CommonAPI-DBus-dev "

libCommonAPI-DBus_files = ""
libCommonAPI-DBus_files += "${prefix}/lib/*so.*"

CommonAPI-DBus-dev_files = ""
CommonAPI-DBus-dev_files += "${prefix}/include/CommonAPI-2.1/CommonAPI/*"
CommonAPI-DBus-dev_files += "${prefix}/include/CommonAPI-2.1/pugixml/*"
CommonAPI-DBus-dev_files += "${prefix}/lib/*.so"
CommonAPI-DBus-dev_files += "${prefix}/lib/pkgconfig/*.pc"

FILES_lib${PN} = "${libCommonAPI-DBus_files}"
FILES_${PN}-dev = "${CommonAPI-DBus-dev_files}"

PKG_libCommonAPI-DBus= "libCommonAPI-DBus"
PKG_CommonAPI-DBus-dev= "CommonAPI-DBus-dev"

require CommonAPI-DBus-extraconf.inc

