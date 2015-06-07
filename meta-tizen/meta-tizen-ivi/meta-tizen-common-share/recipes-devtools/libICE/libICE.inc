DESCRIPTION = "X11 Inter-Client Exchange Library"
HOMEPAGE = "http://xorg.freedesktop.org/"
SECTION = "Graphics/X Window System"
LICENSE = "MIT"
PV = "1.0.8"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by libICE


#PROVIDES by libICE-dev
PROVIDES += "libICE-dev"


RDEPENDS = ""
#RDEPENDS of libICE-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "libICE"


DEPENDS = ""
#DEPENDS of libICE
DEPENDS += "xtrans"
DEPENDS += "util-macros"
DEPENDS += "xproto"
inherit pkgconfig

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/libICE.manifest .
 
 
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
EXTRA_OECONF += " --docdir=${prefix}/share/doc/packages/libICE --disable-static"

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
PACKAGES += " libICE "
PACKAGES += " libICE-dev "

libICE_files = ""
libICE_files += "${prefix}/lib/libICE.so.6*"
MANIFESTFILES_${PN} = "libICE.manifest"

libICE-dev_files = ""
libICE-dev_files += "${prefix}/include/X11/*"
libICE-dev_files += "${prefix}/lib/libICE.so"
libICE-dev_files += "${prefix}/lib/pkgconfig/ice.pc"
libICE-dev_files += "${prefix}/share/doc/packages/libICE"
MANIFESTFILES_${PN}-dev = "libICE.manifest"

FILES_${PN} = "${libICE_files}"
FILES_${PN}-dev = "${libICE-dev_files}"

PKG_libICE= "libICE"
PKG_libICE-dev= "libICE-dev"

require libICE-extraconf.inc

