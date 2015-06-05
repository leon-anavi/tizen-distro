DESCRIPTION = "Hangul input library used by scim-hangul and ibus-hangul"
HOMEPAGE = "http://code.google.com/p/libhangul"
SECTION = "System/Utilities"
LICENSE = "LGPL-2.1"
PV = "0.1.0"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by libhangul-dev
PROVIDES += "libhangul-dev"


#PROVIDES by libhangul


RDEPENDS = ""
#RDEPENDS of libhangul-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "libhangul"


DEPENDS = ""
#DEPENDS of libhangul
#Replace "DEPENDS" on gettext by "inherit gettext"
inherit gettext
inherit pkgconfig

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/libhangul.manifest .
 
 
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
  
  [ ! -x autogen.sh ] ||  rm -f configure
  touch ChangeLog
  
  autotools_do_configure
  oe_runmake ${PARALLEL_MAKE}
  
  
  
}
EXTRA_OECONF += " --disable-static --with-pic"

do_install() {
 export RPM_BUILD_ROOT=${D}
 cd ${S}
 LANG=C
 export LANG
 unset DISPLAY
 rm -rf ${D}
 mkdir -p ${D}
 
 make DESTDIR=${RPM_BUILD_ROOT} install
 rm -f ${D}${prefix}/lib/*.la
 #find_lang libhangul
 
 
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
PACKAGES += " libhangul-dev "
PACKAGES += " libhangul "

libhangul-dev_files = ""
libhangul-dev_files += "${prefix}/include/hangul-1.0/*"
libhangul-dev_files += "${prefix}/lib/lib*.so"
libhangul-dev_files += "${prefix}/lib/pkgconfig/libhangul.pc"
MANIFESTFILES_${PN}-dev = "libhangul.manifest"

libhangul_files = ""
libhangul_files += "AUTHORS NEWS README"
libhangul_files += "${prefix}/lib/lib*.so.*"
libhangul_files += "${prefix}/share/libhangul/hanja/"
libhangul_files += "${prefix}/share/libhangul/hanja/hanja.txt"
libhangul_files += "${prefix}/bin/hangul"
MANIFESTFILES_${PN} = "libhangul.manifest"
DIRFILES_${PN} = ""
DIRFILES_${PN} += "${prefix}/share/libhangul/hanja/"

FILES_${PN}-dev = "${libhangul-dev_files}"
FILES_${PN} = "${libhangul_files}"

PKG_libhangul-dev= "libhangul-dev"
PKG_libhangul= "libhangul"

require libhangul-extraconf.inc

