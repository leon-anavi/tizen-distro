DESCRIPTION = "Library to control OAL APIs"
HOMEPAGE = "http://nohomepage.org"
SECTION = "Application Framework/Libraries"
LICENSE = "Apache-2.0"
PV = "0.1.0"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by libdevice-node


#PROVIDES by libdevice-node-dev
PROVIDES += "libdevice-node-dev"


RDEPENDS = ""
#RDEPENDS of libdevice-node-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "libdevice-node"


DEPENDS = ""
#DEPENDS of libdevice-node
inherit tizen_cmake
inherit pkgconfig
DEPENDS += "dlog"
DEPENDS += "vconf"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/libdevice-node.manifest .
 
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
 make ${PARALLEL_MAKE}
 
 
 
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
PACKAGES += " libdevice-node "
PACKAGES += " libdevice-node-dev "

libdevice-node_files = ""
libdevice-node_files += "${prefix}/lib/*.so.*"
MANIFESTFILES_${PN} = "libdevice-node.manifest"

libdevice-node-dev_files = ""
libdevice-node-dev_files += "${prefix}/include/device-node/*.h"
libdevice-node-dev_files += "${prefix}/lib/*.so"
libdevice-node-dev_files += "${prefix}/lib/pkgconfig/*.pc"

FILES_${PN} = "${libdevice-node_files}"
FILES_${PN}-dev = "${libdevice-node-dev_files}"

PKG_libdevice-node= "libdevice-node"
PKG_libdevice-node-dev= "libdevice-node-dev"

require libdevice-node-extraconf.inc

