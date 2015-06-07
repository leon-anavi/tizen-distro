DESCRIPTION = "opencore AMRNB dev package"
HOMEPAGE = "http://nohomepage.org"
SECTION = "libdevel"
LICENSE = "Apache-2.0"
PV = "0.1.2"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by opencore-amr-dev
PROVIDES += "opencore-amr-dev"


#PROVIDES by opencore-amr


RDEPENDS = ""
#RDEPENDS of opencore-amr-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "opencore-amr"


DEPENDS = ""

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/opencore-amr.manifest .
 
 
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
  
  ./autogen.sh
  
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
 
 rm -rf ${D}
 mkdir -p ${D}/usr/share/license
 cp LICENSE ${D}/usr/share/license/opencore-amr
 
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
PACKAGES += " opencore-amr-dev "
PACKAGES += " opencore-amr "

opencore-amr-dev_files = ""
opencore-amr-dev_files += "${prefix}/include/opencore-amrnb/*.h"
opencore-amr-dev_files += "${prefix}/include/opencore-amrwb/*.h"
opencore-amr-dev_files += "${prefix}/lib/libopencore-amrnb.so"
opencore-amr-dev_files += "${prefix}/lib/libopencore-amrwb.so"
opencore-amr-dev_files += "${prefix}/lib/pkgconfig/opencore-amrnb.pc"
opencore-amr-dev_files += "${prefix}/lib/pkgconfig/opencore-amrwb.pc"
MANIFESTFILES_${PN}-dev = "opencore-amr.manifest"

opencore-amr_files = ""
opencore-amr_files += "${prefix}/lib/libopencore-amrnb.so.0"
opencore-amr_files += "${prefix}/lib/libopencore-amrnb.so.0.0.2"
opencore-amr_files += "${prefix}/lib/libopencore-amrwb.so.0"
opencore-amr_files += "${prefix}/lib/libopencore-amrwb.so.0.0.2"
opencore-amr_files += "${prefix}/share/license/opencore-amr"
MANIFESTFILES_${PN} = "opencore-amr.manifest"

FILES_${PN}-dev = "${opencore-amr-dev_files}"
FILES_${PN} = "${opencore-amr_files}"

PKG_opencore-amr-dev= "opencore-amr-dev"
PKG_opencore-amr= "opencore-amr"

require opencore-amr-extraconf.inc

