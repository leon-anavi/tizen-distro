DESCRIPTION = "Multimedia Framework Utility Library"
HOMEPAGE = "http://nohomepage.org"
SECTION = "System/Libraries"
LICENSE = "Apache-2.0"
PV = "0.7"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by libmm-utility


#PROVIDES by libmm-utility-dev
PROVIDES += "libmm-utility-dev"


#PROVIDES by libmm-utility-tool
PROVIDES += "libmm-utility-tool"


RDEPENDS = ""
#RDEPENDS of libmm-utility (${PN})
RDEPENDS_${PN} += "glibc"

#RDEPENDS of libmm-utility-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "libmm-utility"

#RDEPENDS of libmm-utility-tool (${PN}-tool)
RDEPENDS_${PN}-tool += "libmm-utility"


DEPENDS = ""
#DEPENDS of libmm-utility
DEPENDS += "libmm-common"
DEPENDS += "libjpeg-turbo"
DEPENDS += "libmm-log"
inherit pkgconfig
DEPENDS += "glib-2.0"
DEPENDS += "libmm-ta"
DEPENDS += "tizen-platform-config"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/libmm-utility.manifest .
 
 
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
  
  mkdir -p m4
  CFLAGS="$CFLAGS -DEXPORT_API=\"__attribute__((visibility(\\\"default\\\")))\" -D_MM_PROJECT_FLOATER"   LDFLAGS="$LDFLAGS -Wl,--rpath=${prefix}/lib -Wl,--hash-style=both -Wl,--as-needed"   
  autotools_do_configure
  oe_runmake ${PARALLEL_MAKE}
  
  sed -i -e "s#@IMGP_REQPKG@#$IMGP_REQPKG#g" imgp/mmutil-imgp.pc
  sed -i -e "s#@JPEG_REQPKG@#$JPEG_REQPKG#g" jpeg/mmutil-jpeg.pc
  
  
  
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
PACKAGES += " libmm-utility "
PACKAGES += " libmm-utility-dev "
PACKAGES += " libmm-utility-tool "

libmm-utility_files = ""
libmm-utility_files += "${prefix}/lib/*.so*"
MANIFESTFILES_${PN} = "libmm-utility.manifest"

libmm-utility-dev_files = ""
libmm-utility-dev_files += "${prefix}/include/*"
libmm-utility-dev_files += "${prefix}/lib/pkgconfig/*"
MANIFESTFILES_${PN}-dev = "libmm-utility.manifest"

libmm-utility-tool_files = ""
libmm-utility-tool_files += "${prefix}/bin/*_testsuite"
MANIFESTFILES_${PN}-tool = "libmm-utility.manifest"

FILES_${PN} = "${libmm-utility_files}"
FILES_${PN}-dev = "${libmm-utility-dev_files}"
FILES_${PN}-tool = "${libmm-utility-tool_files}"

PKG_libmm-utility= "libmm-utility"
PKG_libmm-utility-dev= "libmm-utility-dev"
PKG_libmm-utility-tool= "libmm-utility-tool"

require libmm-utility-extraconf.inc

