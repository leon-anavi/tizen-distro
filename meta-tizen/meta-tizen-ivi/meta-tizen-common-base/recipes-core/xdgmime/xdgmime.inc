DESCRIPTION = "Querying information about file type"
HOMEPAGE = "http://nohomepage.org"
SECTION = "Applications/Other"
LICENSE = "LGPL-2.0 and AFL-2.0"
PV = "0.0.12"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by xdgmime-dev
PROVIDES += "xdgmime-dev"


#PROVIDES by xdgmime


RDEPENDS = ""
#RDEPENDS of xdgmime-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "xdgmime"


DEPENDS = ""
#DEPENDS of xdgmime
inherit tizen_cmake

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/xdgmime.manifest .
 
 
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
 
 
   cmake \
         -DCMAKE_VERBOSE_MAKEFILE=ON \
         -DCMAKE_INSTALL_PREFIX:PATH=${prefix} \
         -DCMAKE_INSTALL_LIBDIR:PATH=${prefix}/lib \
         -DINCLUDE_INSTALL_DIR:PATH=${prefix}/include \
         -DLIB_INSTALL_DIR:PATH=${prefix}/lib \
         -DSYSCONF_INSTALL_DIR:PATH=${sysconfdir} \
         -DSHARE_INSTALL_PREFIX:PATH=${prefix}/share \
         -DCMAKE_SKIP_RPATH:BOOL=ON \
         -DBUILD_SHARED_LIBS:BOOL=ON \
         -DCMAKE_TOOLCHAIN_FILE=${WORKDIR}/toolchain.cmake \
         ${EXTRA_OECMAKE} . 
 oe_runmake ${PARALLEL_MAKE}
 
 
 
}

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
PACKAGES += " xdgmime-dev "
PACKAGES += " xdgmime "

xdgmime-dev_files = ""
xdgmime-dev_files += "${prefix}/include/xdgmime.h"
xdgmime-dev_files += "${prefix}/lib/libxdgmime.so"
xdgmime-dev_files += "${prefix}/lib/pkgconfig/xdgmime.pc"
MANIFESTFILES_${PN}-dev = "xdgmime.manifest"

xdgmime_files = ""
xdgmime_files += "${prefix}/lib/libxdgmime.so.*"
MANIFESTFILES_${PN} = "xdgmime.manifest"

FILES_${PN}-dev = "${xdgmime-dev_files}"
FILES_${PN} = "${xdgmime_files}"

PKG_xdgmime-dev= "xdgmime-dev"
PKG_xdgmime= "xdgmime"

require xdgmime-extraconf.inc

