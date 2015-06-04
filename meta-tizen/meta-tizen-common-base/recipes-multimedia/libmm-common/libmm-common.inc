DESCRIPTION = "Multimedia Framework Common Library"
HOMEPAGE = "http://nohomepage.org"
SECTION = "Multimedia/Libraries"
LICENSE = "Apache-2.0"
PV = "0.2.55"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by libmm-common-dev
PROVIDES += "libmm-common-dev"


#PROVIDES by libmm-common


RDEPENDS = ""
#RDEPENDS of libmm-common-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "libmm-common"


DEPENDS = ""
#DEPENDS of libmm-common
DEPENDS += "libmm-log"
inherit pkgconfig
DEPENDS += "glib-2.0"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/libmm-common.manifest .
 
 
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
  
  
  CFLAGS="$CFLAGS -DEXPORT_API=\"__attribute__((visibility(\\\"default\\\")))\" "
  
  autotools_do_configure
  oe_runmake -j16
  
  
  
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
PACKAGES += " libmm-common-dev "
PACKAGES += " libmm-common "

libmm-common-dev_files = ""
libmm-common-dev_files += "${prefix}/include/mmf/SLP_MultimediaFW_PG.h"
libmm-common-dev_files += "${prefix}/include/mmf/mm_types.h"
libmm-common-dev_files += "${prefix}/include/mmf/mm_error.h"
libmm-common-dev_files += "${prefix}/include/mmf/mm_message.h"
libmm-common-dev_files += "${prefix}/include/mmf/mm_attrs.h"
libmm-common-dev_files += "${prefix}/include/mmf/mm_attrs_private.h"
libmm-common-dev_files += "${prefix}/include/mmf/mm_debug.h"
libmm-common-dev_files += "${prefix}/include/mmf/mm.h"
libmm-common-dev_files += "${prefix}/lib/pkgconfig/mm-common.pc"
libmm-common-dev_files += "${prefix}/lib/libmmfcommon.so"
MANIFESTFILES_${PN}-dev = "libmm-common.manifest"

libmm-common_files = ""
libmm-common_files += "${prefix}/lib/libmmfcommon.so.*"
MANIFESTFILES_${PN} = "libmm-common.manifest"

FILES_${PN}-dev = "${libmm-common-dev_files}"
FILES_${PN} = "${libmm-common_files}"

PKG_libmm-common-dev= "libmm-common-dev"
PKG_libmm-common= "libmm-common"

require libmm-common-extraconf.inc

