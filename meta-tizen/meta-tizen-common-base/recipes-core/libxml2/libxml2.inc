DESCRIPTION = "A Library to Manipulate XML Files"
HOMEPAGE = "http://xmlsoft.org"
SECTION = "System/Libraries"
LICENSE = "MIT"
PV = "2.8.0"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by libxml2


#PROVIDES by libxml2-dev
PROVIDES += "libxml2-dev"


#PROVIDES by libxml2-tools
PROVIDES += "libxml2-tools"


RDEPENDS = ""
#RDEPENDS of libxml2-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "libxml2"
RDEPENDS_${PN}-dev += "glibc"
RDEPENDS_${PN}-dev += "zlib"
RDEPENDS_${PN}-dev += "xz"
RDEPENDS_${PN}-dev += "libxml2-tools"
RDEPENDS_${PN}-dev += "readline"


DEPENDS = ""
#DEPENDS of libxml2
DEPENDS += "xz"
DEPENDS_append_class-native = " readline-native"
DEPENDS_append_class-target = " readline-native"
DEPENDS += "zlib"
inherit pkgconfig

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/libxml2.manifest .
 
 
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
  
  make ${PARALLEL_MAKE} BASE_DIR="${prefix}/share/doc/packages" DOC_MODULE="libxml2"
  
  exit 0
  # qemu-arm can't keep up atm, disabling check for arm
  make check
  
  
  
}
EXTRA_OECONF += " --disable-static --docdir=${prefix}/share/doc/packages/libxml2 --with-html-dir=${prefix}/share/doc/packages/libxml2/html --with-fexceptions --with-history --without-python --enable-ipv6 --with-sax1 --with-regexps --with-threads --with-reader --with-http"

do_install() {
 export RPM_BUILD_ROOT=${D}
 cd ${S}
 LANG=C
 export LANG
 unset DISPLAY
 rm -rf ${D}
 mkdir -p ${D}
 
 make install DESTDIR="${D}" BASE_DIR="${prefix}/share/doc/packages" DOC_MODULE="libxml2"
 ln -s libxml2/libxml ${D}${prefix}/include/libxml
 
 
   rm -rf ${D}${infodir} 
   rm -rf ${D}${prefix}/share/doc/packages 
   rm -rf ${D}${prefix}/share/doc/libxml2 
   rm -rf ${D}${prefix}/share/doc/libxml2-2.8.0 
   rm -rf ${D}${prefix}/share/gtk-doc 
   rm -rf ${D}${prefix}/share/doc 
   rm -rf ${D}${prefix}/share/man 
   find ${D} -regex ".*/man/man./.*.[0-9]" | xargs rm -f -- 
   find ${D} -regex ".*/man/../man./.*.[0-9]" | xargs rm -f -- 
   find ${D} -regex ".*/man/man./.*.[0-9]pm" | xargs rm -f --
 
 
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
PACKAGES += " libxml2 "
PACKAGES += " libxml2-dev "
PACKAGES += " libxml2-tools "

libxml2_files = ""
libxml2_files += "${prefix}/lib/lib*.so.*"
MANIFESTFILES_${PN} = "libxml2.manifest"

libxml2-dev_files = ""
libxml2-dev_files += "${prefix}/bin/xml2-config"
libxml2-dev_files += "${prefix}/share/aclocal"
libxml2-dev_files += "${prefix}/share/aclocal/libxml.m4"
libxml2-dev_files += "${prefix}/include/libxml"
libxml2-dev_files += "${prefix}/include/libxml2"
libxml2-dev_files += "${prefix}/lib/lib*.so"
libxml2-dev_files += "${prefix}/lib/libxml2.la"
libxml2-dev_files += "${prefix}/lib/*.sh"
libxml2-dev_files += "${prefix}/lib/pkgconfig/*.pc"
MANIFESTFILES_${PN}-dev = "libxml2.manifest"
DIRFILES_${PN}-dev = ""
DIRFILES_${PN}-dev += "${prefix}/share/aclocal"

libxml2-tools_files = ""
libxml2-tools_files += "${prefix}/bin/xmllint"
libxml2-tools_files += "${prefix}/bin/xmlcatalog"
MANIFESTFILES_${PN}-tools = "libxml2.manifest"

FILES_${PN} = "${libxml2_files}"
FILES_${PN}-dev = "${libxml2-dev_files}"
FILES_${PN}-tools = "${libxml2-tools_files}"

PKG_libxml2= "libxml2"
PKG_libxml2-dev= "libxml2-dev"
PKG_libxml2-tools= "libxml2-tools"

require libxml2-extraconf.inc

