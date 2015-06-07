DESCRIPTION = "GObject Introspection Tools"
HOMEPAGE = "http://live.gnome.org/GObjectIntrospection"
SECTION = "Development/Libraries"
LICENSE = "LGPL-2.1+ and GPL-2.0+"
PV = "1.36.0"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by gobject-introspection


#PROVIDES by gobject-introspection-dev
PROVIDES += "gobject-introspection-dev"


#PROVIDES by girepository
PROVIDES += "girepository"


#PROVIDES by libgirepository
PROVIDES += "libgirepository"


#PROVIDES by gobject-introspection-docs
PROVIDES += "gobject-introspection-docs "


RDEPENDS = ""
#RDEPENDS of gobject-introspection (${PN})
RDEPENDS_${PN} += "python-xml"
RDEPENDS_${PN} += "libgirepository"

#RDEPENDS of gobject-introspection-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "libffi"
RDEPENDS_${PN}-dev += "gobject-introspection"

#RDEPENDS of girepository (girepository)
RDEPENDS_girepository += "libgirepository"

#RDEPENDS of libgirepository (libgirepository)
RDEPENDS_libgirepository += "girepository"


DEPENDS = ""
#DEPENDS of gobject-introspection
DEPENDS += "flex"
inherit pythonnative
DEPENDS += "cairo"
inherit pkgconfig
DEPENDS += "python-xml"
DEPENDS_append_class-native = " libtool"
DEPENDS_append_class-target = " libtool-cross"
DEPENDS += "libffi"
DEPENDS_append_class-native = " bison-native"
DEPENDS_append_class-target = " bison-native"
DEPENDS_append_class-native = " fdupes-native"
DEPENDS_append_class-target = " fdupes-native"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/gobject-introspection.manifest .
 
 
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
  #autoreconf -fi
  
  autotools_do_configure
  oe_runmake ${PARALLEL_MAKE} V=1
  
  
  
}
EXTRA_OECONF += " --disable-gtk-doc "

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
 install -D ${S}/packaging/gi-find-deps.sh ${D}/usr/share/spec2yocto/macro/gi-find-deps.sh
 install -D ${S}/packaging/gobjectintrospection.attr -m 0644 ${D}/usr/share/spec2yocto/macro/fileattrs/gobjectintrospection.attr
 # comparing, if we provide all the symbols expected.
 ls ${D}${prefix}/lib/girepository-1.0/*.typelib | sh ${S}/packaging/gi-find-deps.sh -P > gobject-introspection-typelib.installed
 diff -s ${S}/packaging/gobject-introspection-typelib.template gobject-introspection-typelib.installed
 #fdupes ${D}
 
 
 
}

pkg_postinst_libgirepository() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_libgirepository() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " gobject-introspection "
PACKAGES += " gobject-introspection-dev "
PACKAGES += " girepository "
PACKAGES += " libgirepository "
PACKAGES += " gobject-introspection-docs "

gobject-introspection_files = ""
gobject-introspection_files += "${prefix}/bin/g-ir-annotation-tool"
gobject-introspection_files += "${prefix}/bin/g-ir-compiler"
gobject-introspection_files += "${prefix}/bin/g-ir-dep-tool"
gobject-introspection_files += "${prefix}/bin/g-ir-generate"
gobject-introspection_files += "${prefix}/bin/g-ir-scanner"
gobject-introspection_files += "${prefix}/share/aclocal/introspection.m4"
gobject-introspection_files += "${prefix}/share/gir-1.0/*.gir"
gobject-introspection_files += "${prefix}/lib/gobject-introspection"
gobject-introspection_files += "${prefix}/lib/gobject-introspection/giscanner/"
gobject-introspection_files += "${prefix}/share/gobject-introspection-1.0"
gobject-introspection_files += "${prefix}/share/gobject-introspection-1.0/Makefile.introspection"
gobject-introspection_files += "${prefix}/share/gobject-introspection-1.0/tests/"
gobject-introspection_files += "${prefix}/share/gobject-introspection-1.0/gdump.c"
gobject-introspection_files += "/usr/share/spec2yocto/macro/gi-find-deps.sh"
gobject-introspection_files += "/usr/share/spec2yocto/macro/fileattrs/gobjectintrospection.attr"
MANIFESTFILES_${PN} = "gobject-introspection.manifest"
DIRFILES_${PN} = ""
DIRFILES_${PN} += "${prefix}/lib/gobject-introspection"
DIRFILES_${PN} += "${prefix}/share/gobject-introspection-1.0"

gobject-introspection-dev_files = ""
gobject-introspection-dev_files += "${prefix}/include/gobject-introspection-1.0/"
gobject-introspection-dev_files += "${prefix}/lib/libgirepository-1.0.so"
gobject-introspection-dev_files += "${prefix}/lib/pkgconfig/gobject-introspection-1.0.pc"
gobject-introspection-dev_files += "${prefix}/lib/pkgconfig/gobject-introspection-no-export-1.0.pc"
MANIFESTFILES_${PN}-dev = "gobject-introspection.manifest"

girepository_files = ""
girepository_files += "${prefix}/lib/girepository-1.0/*.typelib"
MANIFESTFILES_girepository = "gobject-introspection.manifest"

libgirepository_files = ""
libgirepository_files += "COPYING.LGPL"
libgirepository_files += "${prefix}/share/gir-1.0"
libgirepository_files += "${prefix}/lib/libgirepository-1.0.so.*"
libgirepository_files += "${prefix}/lib/girepository-1.0"
MANIFESTFILES_libgirepository = "gobject-introspection.manifest"
DIRFILES_libgirepository = ""
DIRFILES_libgirepository += "${prefix}/share/gir-1.0"
DIRFILES_libgirepository += "${prefix}/lib/girepository-1.0"

gobject-introspection-docs_files = ""

FILES_${PN} = "${gobject-introspection_files}"
FILES_${PN}-dev = "${gobject-introspection-dev_files}"
FILES_girepository = "${girepository_files}"
FILES_libgirepository = "${libgirepository_files}"
FILES_${PN}-docs = "${gobject-introspection-docs_files}"

PKG_gobject-introspection= "gobject-introspection"
PKG_gobject-introspection-dev= "gobject-introspection-dev"
PKG_girepository= "girepository"
PKG_libgirepository= "libgirepository"
PKG_gobject-introspection-docs= "gobject-introspection-docs"

require gobject-introspection-extraconf.inc

