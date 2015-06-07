DESCRIPTION = "Tools for Converting from and to the Tiff Format"
HOMEPAGE = "http://www.remotesensing.org/libtiff"
SECTION = "Productivity/Graphics/Convertors"
LICENSE = "HPND"
PV = "4.0.3"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by libtiff
PROVIDES += "libtiff"


#PROVIDES by tiff


#PROVIDES by tiff-docs
PROVIDES += "tiff-docs "


#PROVIDES by libtiff-dev
PROVIDES += "libtiff-dev"


RDEPENDS = ""
#RDEPENDS of libtiff-dev (lib${PN}-dev)
RDEPENDS_lib${PN}-dev += "glibc"
RDEPENDS_lib${PN}-dev += "libtiff"
RDEPENDS_lib${PN}-dev += "libstdc++-dev"


DEPENDS = ""
#DEPENDS of tiff
DEPENDS += "libjpeg-turbo"
DEPENDS += "zlib"
inherit pkgconfig
DEPENDS += "xz"
DEPENDS_append_class-native = " libtool"
DEPENDS_append_class-target = " libtool-cross"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/tiff.manifest .
 
 
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
  make ${PARALLEL_MAKE}
  
  
  
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
 
 mkdir -p ${D}/{${mandir}/{man1,man3},usr/{bin,lib,include}}
 
   oe_runmake \
         DESTDIR=${D} \
         INSTALL_ROOT=${D} \
         BINDIR=${prefix}/bin \
   install  
   rm -f ${D}${infodir}/dir 
   find ${D} -regex ".*\.la$" | xargs rm -f -- 
   find ${D} -regex ".*\.a$" | xargs rm -f --
 for f in `find ${D}/${mandir} -type f -print ` ; do
   if [ `wc -l <$f` -eq 1 ] && grep -q "^\.so " $f ; then
     linkto=`sed -e "s|^\.so ||" $f`
     [ -f "`dirname $f`/$linkto" ] && ln -sf "$linkto" $f
   fi
 done
 
 rm -rf ${D}${prefix}/share/doc/tiff*
 rm -f ${D}${prefix}/lib/*.la
 find html -name "Makefile*" | xargs rm
 
 
 
 
}

pkg_postinst_libtiff() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_libtiff() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " tiff "
PACKAGES += " tiff-docs "
PACKAGES += " libtiff "
PACKAGES += " libtiff-dev "

tiff_files = ""
tiff_files += "${prefix}/bin/*"
MANIFESTFILES_${PN} = "tiff.manifest"

tiff-docs_files = ""

libtiff_files = ""
libtiff_files += "${prefix}/lib/*.so.*"
MANIFESTFILES_lib${PN} = "tiff.manifest"

libtiff-dev_files = ""
libtiff-dev_files += "${prefix}/include/*"
libtiff-dev_files += "${prefix}/lib/*.so"
libtiff-dev_files += "${prefix}/lib/pkgconfig/*.pc"
MANIFESTFILES_lib${PN}-dev = "tiff.manifest"

FILES_${PN} = "${tiff_files}"
FILES_${PN}-docs = "${tiff-docs_files}"
FILES_lib${PN} = "${libtiff_files}"
FILES_lib${PN}-dev = "${libtiff-dev_files}"

PKG_tiff= "tiff"
PKG_tiff-docs= "tiff-docs"
PKG_libtiff= "libtiff"
PKG_libtiff-dev= "libtiff-dev"

require tiff-extraconf.inc

