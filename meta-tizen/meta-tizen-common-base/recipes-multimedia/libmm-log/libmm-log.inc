DESCRIPTION = "Multimedia Framework LOG Lib"
HOMEPAGE = "http://nohomepage.org"
SECTION = "Multimedia/Multimedia Framework"
LICENSE = "Apache-2.0"
PV = "0.1.5"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by libmm-log


#PROVIDES by libmm-log-dev
PROVIDES += "libmm-log-dev"


RDEPENDS = ""

DEPENDS = ""
#DEPENDS of libmm-log
inherit pkgconfig
DEPENDS += "dlog"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q -n libmm-log-0.1.5
 cp ${S}/packaging/libmm-log.manifest .
 
 
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
  
  CFLAGS="$CFLAGS -DUSE_DLOG"; export CFLAGS
  ./autogen.sh
  
  autotools_do_configure
  oe_runmake ${PARALLEL_MAKE}
  
  
  
}
EXTRA_OECONF += " --disable-static --enable-dlog"

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

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " libmm-log-dev "

libmm-log-dev_files = ""
libmm-log-dev_files += "${prefix}/include/mm_log/mm_log.h"
libmm-log-dev_files += "${prefix}/lib/pkgconfig/mm-log.pc"
MANIFESTFILES_${PN}-dev = "libmm-log.manifest"

FILES_${PN}-dev = "${libmm-log-dev_files}"

PKG_libmm-log-dev= "libmm-log-dev"

require libmm-log-extraconf.inc

