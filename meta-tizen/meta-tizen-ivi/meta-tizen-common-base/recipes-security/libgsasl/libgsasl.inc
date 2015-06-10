DESCRIPTION = "Library for perfoming SASL authentication"
HOMEPAGE = "http://nohomepage.org"
SECTION = "Security/Accounts"
LICENSE = "LGPL-2.1+"
PV = "1.8.0"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by libgsasl-dev
PROVIDES += "libgsasl-dev"


#PROVIDES by libgsasl


RDEPENDS = ""
#RDEPENDS of libgsasl-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "libgsasl"

#RDEPENDS of libgsasl (${PN})
RDEPENDS_${PN} += "glibc"


DEPENDS = ""
#DEPENDS of libgsasl
DEPENDS += "libgcrypt"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q -n libgsasl-1.8.0
 cp ${S}/packaging/libgsasl.manifest .
 
 
 
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
EXTRA_OECONF += " --with-libgcrypt"

do_install() {
 export RPM_BUILD_ROOT=${D}
 cd ${S}
 LANG=C
 export LANG
 unset DISPLAY
 rm -rf ${D}
 mkdir -p ${D}
 
 rm -rf ${D}
 
   oe_runmake \
         DESTDIR=${D} \
         INSTALL_ROOT=${D} \
         BINDIR=${prefix}/bin \
   install  
   rm -f ${D}${infodir}/dir 
   find ${D} -regex ".*\.la$" | xargs rm -f -- 
   find ${D} -regex ".*\.a$" | xargs rm -f --
 
 #find_lang libgsasl
 
 
 
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
PACKAGES += " libgsasl-dev "
PACKAGES += " libgsasl "

libgsasl-dev_files = ""
libgsasl-dev_files += "${prefix}/include/gsasl*.h"
libgsasl-dev_files += "${prefix}/lib/libgsasl.so"
libgsasl-dev_files += "${prefix}/lib/pkgconfig/libgsasl.pc"
MANIFESTFILES_${PN}-dev = "libgsasl.manifest"

libgsasl_files = ""
libgsasl_files += "AUTHORS NEWS README THANKS"
libgsasl_files += "${prefix}/lib/libgsasl.so.*"
MANIFESTFILES_${PN} = "libgsasl.manifest"

FILES_${PN}-dev = "${libgsasl-dev_files}"
FILES_${PN} = "${libgsasl_files}"

PKG_libgsasl-dev= "libgsasl-dev"
PKG_libgsasl= "libgsasl"

require libgsasl-extraconf.inc

