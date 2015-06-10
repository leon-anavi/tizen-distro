DESCRIPTION = "Library to deal with pinyin"
HOMEPAGE = "http://nohomepage.org"
SECTION = "System/Libraries"
LICENSE = "GPL-2.0+"
PV = "1.0.0"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by libpinyin


#PROVIDES by libpinyin-dev
PROVIDES += "libpinyin-dev"


#PROVIDES by libpinyin-tools
PROVIDES += "libpinyin-tools"


RDEPENDS = ""
#RDEPENDS of libpinyin-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "libpinyin"

#RDEPENDS of libpinyin-tools (${PN}-tools)
RDEPENDS_${PN}-tools += "libpinyin"


DEPENDS = ""
#DEPENDS of libpinyin
DEPENDS += "db"
inherit pkgconfig
DEPENDS += "glib-2.0"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/libpinyin.manifest .
 
 
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
   find ${D} -regex ".*\.a$" | xargs rm -f -- DESTDIR=${D}
 find ${D} -name '*.la' -exec rm -f {} ';'
 
 
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
PACKAGES += " libpinyin "
PACKAGES += " libpinyin-dev "
PACKAGES += " libpinyin-tools "

libpinyin_files = ""
libpinyin_files += "AUTHORS README"
libpinyin_files += "${prefix}/lib/*.so.*"
libpinyin_files += "${prefix}/lib/libpinyin"
libpinyin_files += "${prefix}/lib/libpinyin/data"
MANIFESTFILES_${PN} = "libpinyin.manifest"
DIRFILES_${PN} = ""
DIRFILES_${PN} += "${prefix}/lib/libpinyin"

libpinyin-dev_files = ""
libpinyin-dev_files += "${prefix}/include/libpinyin-1.0.0"
libpinyin-dev_files += "${prefix}/include/libpinyin-1.0.0/*"
libpinyin-dev_files += "${prefix}/lib/*.so"
libpinyin-dev_files += "${prefix}/lib/pkgconfig/libpinyin.pc"
MANIFESTFILES_${PN}-dev = "libpinyin.manifest"
DIRFILES_${PN}-dev = ""
DIRFILES_${PN}-dev += "${prefix}/include/libpinyin-1.0.0"

libpinyin-tools_files = ""
libpinyin-tools_files += "${prefix}/bin/gen_binary_files"
libpinyin-tools_files += "${prefix}/bin/import_interpolation"
libpinyin-tools_files += "${prefix}/bin/gen_unigram"
libpinyin-tools_files += "${mandir}/man1/*.1.*"
MANIFESTFILES_${PN}-tools = "libpinyin.manifest"

FILES_${PN} = "${libpinyin_files}"
FILES_${PN}-dev = "${libpinyin-dev_files}"
FILES_${PN}-tools = "${libpinyin-tools_files}"

PKG_libpinyin= "libpinyin"
PKG_libpinyin-dev= "libpinyin-dev"
PKG_libpinyin-tools= "libpinyin-tools"

require libpinyin-extraconf.inc

