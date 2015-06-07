DESCRIPTION = "An IRI parsing library"
HOMEPAGE = "http://code.google.com/p/libiri/"
SECTION = "System/Libraries"
LICENSE = "BSD-3-Clause"
PV = "1.1"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by libiri-dev
PROVIDES += "libiri-dev"


#PROVIDES by libiri


RDEPENDS = ""
#RDEPENDS of libiri-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "libiri"


DEPENDS = ""
#DEPENDS of libiri
DEPENDS_append_class-native = " autoconf-native"
DEPENDS_append_class-target = " autoconf-native"
DEPENDS_append_class-native = " libtool"
DEPENDS_append_class-target = " libtool-cross"
DEPENDS_append_class-native = " automake-native"
DEPENDS_append_class-target = " automake-native"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/libiri.manifest .
 
 
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

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " libiri-dev "
PACKAGES += " libiri "

libiri-dev_files = ""
libiri-dev_files += "${prefix}/lib/pkgconfig/*.pc"
libiri-dev_files += "${prefix}/include/*.h"
libiri-dev_files += "/usr/bin/iri-config"
MANIFESTFILES_${PN}-dev = "libiri.manifest"

libiri_files = ""
libiri_files += "${prefix}/lib/*.so"
MANIFESTFILES_${PN} = "libiri.manifest"

FILES_${PN}-dev = "${libiri-dev_files}"
FILES_${PN} = "${libiri_files}"

PKG_libiri-dev= "libiri-dev"
PKG_libiri= "libiri"

require libiri-extraconf.inc

