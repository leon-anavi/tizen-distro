DESCRIPTION = "A toolkit to generate the libtizen-platform-config library"
HOMEPAGE = "http://www.tizen.org"
SECTION = "Development/Tools"
LICENSE = "LGPL-2.0"
PV = "2.0"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by tizen-platform-wrapper


RDEPENDS = ""
#RDEPENDS of tizen-platform-wrapper (${PN})
RDEPENDS_${PN} += "coreutils"
RDEPENDS_${PN} += "gperf"


DEPENDS = ""

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/tizen-platform-wrapper.manifest .
 
 
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
PACKAGES += " tizen-platform-wrapper "

tizen-platform-wrapper_files = ""
tizen-platform-wrapper_files += "${prefix}/bin/*"
tizen-platform-wrapper_files += "${prefix}/share/tizen-platform-wrapper/*"
tizen-platform-wrapper_files += "${prefix}/lib/pkgconfig/tizen-platform-wrapper.pc"
MANIFESTFILES_${PN} = "tizen-platform-wrapper.manifest"

FILES_${PN} = "${tizen-platform-wrapper_files}"

PKG_tizen-platform-wrapper= "tizen-platform-wrapper"

require tizen-platform-wrapper-extraconf.inc

