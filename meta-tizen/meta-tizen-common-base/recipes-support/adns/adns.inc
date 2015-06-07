DESCRIPTION = "Advanced Easy-to-Use Asynchronous-Capable DNS Utilities"
HOMEPAGE = "http://www.chiark.greenend.org.uk/~ian/adns/"
SECTION = "System/Utilities"
LICENSE = "GPL-2.0+"
PV = "1.4"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by libadns
PROVIDES += "libadns"


#PROVIDES by adns


#PROVIDES by libadns-dev
PROVIDES += "libadns-dev"


RDEPENDS = ""
#RDEPENDS of libadns-dev (lib${PN}-dev)
RDEPENDS_lib${PN}-dev += "libadns"
RDEPENDS_lib${PN}-dev += "glibc"


DEPENDS = ""
#DEPENDS of adns
DEPENDS_append_class-native = " autoconf-native"
DEPENDS_append_class-target = " autoconf-native"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/adns.manifest .
 
 
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
  oe_runmake ${PARALLEL_MAKE} all
  
  
  
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

pkg_postinst_libadns() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_libadns() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " libadns "
PACKAGES += " adns "
PACKAGES += " libadns-dev "

libadns_files = ""
libadns_files += "${prefix}/lib/libadns.so.1*"
MANIFESTFILES_lib${PN} = "adns.manifest"

adns_files = ""
adns_files += "${prefix}/bin/adns*"
MANIFESTFILES_${PN} = "adns.manifest"

libadns-dev_files = ""
libadns-dev_files += "${prefix}/include/adns.h"
libadns-dev_files += "${prefix}/lib/libadns.so"
MANIFESTFILES_lib${PN}-dev = "adns.manifest"

FILES_lib${PN} = "${libadns_files}"
FILES_${PN} = "${adns_files}"
FILES_lib${PN}-dev = "${libadns-dev_files}"

PKG_libadns= "libadns"
PKG_adns= "adns"
PKG_libadns-dev= "libadns-dev"

require adns-extraconf.inc

