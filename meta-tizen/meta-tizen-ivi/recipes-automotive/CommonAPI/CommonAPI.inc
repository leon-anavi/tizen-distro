DESCRIPTION = "GENIVI IPC Common API C++ Runtime"
HOMEPAGE = "http://nohomepage.org"
SECTION = "Automotive/GENIVI"
LICENSE = "MPL-2.0"
PV = "2.1.6"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by CommonAPI


#PROVIDES by libCommonAPI
PROVIDES += "libCommonAPI"


#PROVIDES by CommonAPI-dev
PROVIDES += "CommonAPI-dev"


RDEPENDS = ""
#RDEPENDS of CommonAPI (${PN})
RDEPENDS_${PN} += "glibc"

#RDEPENDS of CommonAPI-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "libCommonAPI"


DEPENDS = ""

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
  
  make ${PARALLEL_MAKE}
  
  
  
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
 
 
}

pkg_postinst_libCommonAPI() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_libCommonAPI() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " libCommonAPI "
PACKAGES += " CommonAPI-dev "

libCommonAPI_files = ""
libCommonAPI_files += "${prefix}/lib/*so.*"

CommonAPI-dev_files = ""
CommonAPI-dev_files += "${prefix}/include/CommonAPI-2.1/CommonAPI/*"
CommonAPI-dev_files += "${prefix}/lib/*.so"
CommonAPI-dev_files += "${prefix}/lib/pkgconfig/*.pc"

FILES_lib${PN} = "${libCommonAPI_files}"
FILES_${PN}-dev = "${CommonAPI-dev_files}"

PKG_libCommonAPI= "libCommonAPI"
PKG_CommonAPI-dev= "CommonAPI-dev"

require CommonAPI-extraconf.inc

