DESCRIPTION = "X Session Management library"
HOMEPAGE = "http://xorg.freedesktop.org/"
SECTION = "Graphics/X Window System"
LICENSE = "MIT"
PV = "1.2.1"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by libSM-dev
PROVIDES += "libSM-dev"


#PROVIDES by libSM


RDEPENDS = ""
#RDEPENDS of libSM-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "libSM"


DEPENDS = ""
#DEPENDS of libSM
DEPENDS += "xtrans"
DEPENDS += "xproto"
inherit pkgconfig
DEPENDS += "libICE"
DEPENDS += "util-macros"
DEPENDS += "util-linux"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/libSM.manifest .
 
 
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
EXTRA_OECONF += " --with-libuuid --docdir=${prefix}/share/doc/packages/libSM --disable-static"

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
PACKAGES += " libSM-dev "
PACKAGES += " libSM "

libSM-dev_files = ""
libSM-dev_files += "${prefix}/include/X11/*"
libSM-dev_files += "${prefix}/lib/libSM.so"
libSM-dev_files += "${prefix}/lib/pkgconfig/sm.pc"
libSM-dev_files += "${prefix}/share/doc/packages/libSM"
MANIFESTFILES_${PN}-dev = "libSM.manifest"

libSM_files = ""
libSM_files += "${prefix}/lib/libSM.so.6*"
MANIFESTFILES_${PN} = "libSM.manifest"

FILES_${PN}-dev = "${libSM-dev_files}"
FILES_${PN} = "${libSM_files}"

PKG_libSM-dev= "libSM-dev"
PKG_libSM= "libSM"

require libSM-extraconf.inc

