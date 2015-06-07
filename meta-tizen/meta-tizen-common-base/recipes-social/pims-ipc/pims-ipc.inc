DESCRIPTION = "library for PIMs IPC"
HOMEPAGE = "http://nohomepage.org"
SECTION = "System/Libraries"
LICENSE = "Apache-2.0"
PV = "0.0.28"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by pims-ipc


#PROVIDES by pims-ipc-dev
PROVIDES += "pims-ipc-dev"


RDEPENDS = ""
#RDEPENDS of pims-ipc-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "pims-ipc"


DEPENDS = ""
#DEPENDS of pims-ipc
DEPENDS += "systemd"
inherit tizen_cmake
inherit pkgconfig
DEPENDS += "dlog"
DEPENDS += "glib-2.0"
DEPENDS += "zeromq"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/pims-ipc.manifest .
 
 
 
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
PACKAGES += " pims-ipc "
PACKAGES += " pims-ipc-dev "

pims-ipc_files = ""
pims-ipc_files += "${prefix}/lib/libpims-ipc.so.*"
MANIFESTFILES_${PN} = "pims-ipc.manifest"

pims-ipc-dev_files = ""
pims-ipc-dev_files += "${prefix}/include/pims-ipc/*.h"
pims-ipc-dev_files += "${prefix}/lib/*.so"
pims-ipc-dev_files += "${prefix}/lib/pims_ipc_test"
pims-ipc-dev_files += "${prefix}/lib/pkgconfig/pims-ipc.pc"
MANIFESTFILES_${PN}-dev = "pims-ipc.manifest"

FILES_${PN} = "${pims-ipc_files}"
FILES_${PN}-dev = "${pims-ipc-dev_files}"

PKG_pims-ipc= "pims-ipc"
PKG_pims-ipc-dev= "pims-ipc-dev"

require pims-ipc-extraconf.inc

