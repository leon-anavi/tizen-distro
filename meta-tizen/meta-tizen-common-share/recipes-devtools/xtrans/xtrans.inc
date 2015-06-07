DESCRIPTION = "Library to handle network protocol transport in X"
HOMEPAGE = "http://xorg.freedesktop.org/"
SECTION = "Development/Libraries/X11"
LICENSE = "MIT"
PV = "1.3.4"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by xtrans


RDEPENDS = ""

DEPENDS = ""
#DEPENDS of xtrans
DEPENDS += "util-macros"
inherit pkgconfig

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/xtrans.manifest .
 
 
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
EXTRA_OECONF += " --docdir=${prefix}/share/doc/packages/xtrans"

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

pkg_preinst_${PN}() {
    #!/bin/sh -e

    test -L usr/include/X11 && rm usr/include/X11
    exit 0

}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " xtrans "

xtrans_files = ""
xtrans_files += "${prefix}/share/doc/packages/xtrans/xtrans.xml"
xtrans_files += "${prefix}/include/X11/Xtrans/"
xtrans_files += "${prefix}/share/aclocal/xtrans.m4"
xtrans_files += "${prefix}/share/pkgconfig/xtrans.pc"
MANIFESTFILES_${PN} = "xtrans.manifest"

FILES_${PN} = "${xtrans_files}"

PKG_xtrans= "xtrans"

require xtrans-extraconf.inc

