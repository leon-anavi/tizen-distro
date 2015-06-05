DESCRIPTION = "Multimedia Session Library"
HOMEPAGE = "http://nohomepage.org"
SECTION = "Multimedia/Libraries"
LICENSE = "Apache-2.0"
PV = "0.2.6"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by libmm-session


#PROVIDES by libmm-session-dev
PROVIDES += "libmm-session-dev"


RDEPENDS = ""
#RDEPENDS of libmm-session-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "libmm-session"


DEPENDS = ""
#DEPENDS of libmm-session
DEPENDS += "audio-session-manager"
DEPENDS += "libmm-common"
inherit pkgconfig

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/libmm-session.manifest .
 
 
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
  
  CFLAGS="$CFLAGS -Wp,-D_FORTIFY_SOURCE=0"
  
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
PACKAGES += " libmm-session "
PACKAGES += " libmm-session-dev "

libmm-session_files = ""
libmm-session_files += "${prefix}/lib/libmmfsession.so.*"
MANIFESTFILES_${PN} = "libmm-session.manifest"

libmm-session-dev_files = ""
libmm-session-dev_files += "${prefix}/include/mmf/*.h"
libmm-session-dev_files += "${prefix}/lib/libmmfsession.so"
libmm-session-dev_files += "${prefix}/lib/pkgconfig/mm-session.pc"
MANIFESTFILES_${PN}-dev = "libmm-session.manifest"

FILES_${PN} = "${libmm-session_files}"
FILES_${PN}-dev = "${libmm-session-dev_files}"

PKG_libmm-session= "libmm-session"
PKG_libmm-session-dev= "libmm-session-dev"

require libmm-session-extraconf.inc

