DESCRIPTION = "GLib API for the SSO framework"
HOMEPAGE = "http://nohomepage.org"
SECTION = "Security/Accounts"
LICENSE = "LGPL-2.1"
PV = "2.3.0"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by libgsignon-glib-dev
PROVIDES += "libgsignon-glib-dev"


#PROVIDES by libgsignon-glib


#PROVIDES by libgsignon-glib-doc
PROVIDES += "libgsignon-glib-doc"


RDEPENDS = ""
#RDEPENDS of libgsignon-glib-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "libgsignon-glib"

#RDEPENDS of libgsignon-glib (${PN})
RDEPENDS_${PN} += "gsignon"
RDEPENDS_${PN} += "gsignond-plugin-oauth"
RDEPENDS_${PN} += "dbus"
RDEPENDS_${PN} += "glibc"
RDEPENDS_${PN} += "gsignond-plugin-sasl"


DEPENDS = ""
#DEPENDS of libgsignon-glib
DEPENDS += "libcheck"
inherit pkgconfig
DEPENDS += "glib-2.0"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q -n libgsignon-glib-2.3.0
 cp ${S}/packaging/libgsignon-glib.manifest .
 
 
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
EXTRA_OECONF += " --enable-dbus-type=p2p"

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
PACKAGES += " libgsignon-glib-dev "
PACKAGES += " libgsignon-glib "

libgsignon-glib-dev_files = ""
libgsignon-glib-dev_files += "${prefix}/include/libgsignon-glib/*.h"
libgsignon-glib-dev_files += "${prefix}/lib/libgsignon-glib.so"
libgsignon-glib-dev_files += "${prefix}/lib/pkgconfig/libgsignon-glib.pc"
libgsignon-glib-dev_files += "${prefix}/bin/gsso-example"
MANIFESTFILES_${PN}-dev = "libgsignon-glib.manifest"

libgsignon-glib_files = ""
libgsignon-glib_files += "AUTHORS ChangeLog NEWS README"
libgsignon-glib_files += "${prefix}/lib/libgsignon-glib.so.*"
MANIFESTFILES_${PN} = "libgsignon-glib.manifest"

libgsignon-glib-doc_files = ""
libgsignon-glib-doc_files += "${prefix}/share/gtk-doc/html/libgsignon-glib/*"

FILES_${PN}-dev = "${libgsignon-glib-dev_files}"
FILES_${PN} = "${libgsignon-glib_files}"
FILES_${PN}-doc = "${libgsignon-glib-doc_files}"

PKG_libgsignon-glib-dev= "libgsignon-glib-dev"
PKG_libgsignon-glib= "libgsignon-glib"
PKG_libgsignon-glib-doc= "libgsignon-glib-doc"

require libgsignon-glib-extraconf.inc

