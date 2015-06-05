DESCRIPTION = "Network Client library (Shared library)"
HOMEPAGE = "http://nohomepage.org"
SECTION = "System/Network"
LICENSE = "Flora License"
PV = "0.1.77_55"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by libnet-client-dev
PROVIDES += "libnet-client-dev"


#PROVIDES by libnet-client


RDEPENDS = ""
#RDEPENDS of libnet-client-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "libnet-client"

#RDEPENDS of libnet-client (${PN})
RDEPENDS_${PN} += "glibc"


DEPENDS = ""
#DEPENDS of libnet-client
inherit tizen_cmake
inherit pkgconfig
DEPENDS += "dlog"
DEPENDS += "glib-2.0"
DEPENDS += "vconf"
DEPENDS += "dbus-glib"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/libnet-client.manifest .
 
 
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
  
  mkdir -p m4
  
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
 
 #License
 mkdir -p ${D}${prefix}/share/license
 cp LICENSE.Flora ${D}${prefix}/share/license/libnet-client
 
 #Make test app
 cd test
 mkdir ./lib
 cp -rf ${D}${prefix}/lib/* ./lib/
 ./build.sh
 cd ..
 
 
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
PACKAGES += " libnet-client-dev "
PACKAGES += " libnet-client "

libnet-client-dev_files = ""
libnet-client-dev_files += "${prefix}/include/network/*.h"
libnet-client-dev_files += "${prefix}/lib/pkgconfig/network.pc"
MANIFESTFILES_${PN}-dev = "libnet-client.manifest"

libnet-client_files = ""
libnet-client_files += "${prefix}/lib/libnetwork.so"
libnet-client_files += "${prefix}/lib/libnetwork.so.0"
libnet-client_files += "${prefix}/lib/libnetwork.so.0.0.0"
libnet-client_files += "${prefix}/share/license/libnet-client"
MANIFESTFILES_${PN} = "libnet-client.manifest"

FILES_${PN}-dev = "${libnet-client-dev_files}"
FILES_${PN} = "${libnet-client_files}"

PKG_libnet-client-dev= "libnet-client-dev"
PKG_libnet-client= "libnet-client"

require libnet-client-extraconf.inc

