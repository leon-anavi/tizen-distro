DESCRIPTION = "GObject-based library providing commonly used data structures"
HOMEPAGE = "http://live.gnome.org/Libgee"
SECTION = "System/Libraries"
LICENSE = "LGPL-2.1+"
PV = "0.10.5"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by typelib-Gee
PROVIDES += "typelib-Gee"


#PROVIDES by libgee


#PROVIDES by libgee-dev
PROVIDES += "libgee-dev"


RDEPENDS = ""
#RDEPENDS of libgee (${PN})
RDEPENDS_${PN} += "glibc"

#RDEPENDS of libgee-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "typelib-Gee"
RDEPENDS_${PN}-dev += "libgee"


DEPENDS = ""
#DEPENDS of libgee
DEPENDS += "gtk-doc-stub"
DEPENDS += "vala"
inherit pkgconfig
DEPENDS += "gnome-common"
DEPENDS += "glib-2.0"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 
 
 
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
  
  
  [ -x ./autogen.sh ] && NOCONFIGURE=1 ./autogen.sh
  
  
  autotools_do_configure
  
  make ${PARALLEL_MAKE}
  
  
  
}
EXTRA_OECONF += " --disable-static"

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
PACKAGES += " typelib-Gee "
PACKAGES += " libgee "
PACKAGES += " libgee-dev "

typelib-Gee_files = ""
typelib-Gee_files += "${prefix}/lib/girepository-1.0/Gee-0.8.typelib"

libgee_files = ""
libgee_files += "${prefix}/lib/*.so.*"

libgee-dev_files = ""
libgee-dev_files += "${prefix}/include/gee-0.8/"
libgee-dev_files += "${prefix}/lib/*.so"
libgee-dev_files += "${prefix}/lib/pkgconfig/*.pc"
libgee-dev_files += "${prefix}/share/gir-1.0/*.gir"
libgee-dev_files += "${prefix}/share/vala"
libgee-dev_files += "${prefix}/share/vala/vapi"
libgee-dev_files += "${prefix}/share/vala/vapi/*.vapi"
DIRFILES_${PN}-dev = ""
DIRFILES_${PN}-dev += "${prefix}/share/vala"
DIRFILES_${PN}-dev += "${prefix}/share/vala/vapi"

FILES_typelib-Gee = "${typelib-Gee_files}"
FILES_${PN} = "${libgee_files}"
FILES_${PN}-dev = "${libgee-dev_files}"

PKG_typelib-Gee= "typelib-Gee"
PKG_libgee= "libgee"
PKG_libgee-dev= "libgee-dev"

require libgee-extraconf.inc

