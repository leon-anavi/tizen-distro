DESCRIPTION = "App Checker"
HOMEPAGE = "http://nohomepage.org"
SECTION = "System/Libraries"
LICENSE = "Apache-2.0"
PV = "0.0.16"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by app-checker-server-dev
PROVIDES += "app-checker-server-dev"


#PROVIDES by app-checker-dev
PROVIDES += "app-checker-dev"


#PROVIDES by app-checker


#PROVIDES by app-checker-server
PROVIDES += "app-checker-server"


RDEPENDS = ""
#RDEPENDS of app-checker-server-dev (${PN}-server-dev)
RDEPENDS_${PN}-server-dev += "app-checker-server"

#RDEPENDS of app-checker-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "app-checker"

#RDEPENDS of app-checker-server (${PN}-server)
RDEPENDS_${PN}-server += "app-checker"


DEPENDS = ""
#DEPENDS of app-checker
inherit tizen_cmake
inherit pkgconfig
DEPENDS += "dlog"
DEPENDS += "glib-2.0"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/app-checker.manifest .
 
 
 
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
 
 rm -rf ${D}
 
   oe_runmake \
         DESTDIR=${D} \
         INSTALL_ROOT=${D} \
         BINDIR=${prefix}/bin \
   install  
   rm -f ${D}${infodir}/dir 
   find ${D} -regex ".*\.la$" | xargs rm -f -- 
   find ${D} -regex ".*\.a$" | xargs rm -f --
 mkdir -p ${D}${prefix}/lib/ac-plugins
 
 mkdir -p ${D}/usr/share/license
 cp LICENSE ${D}/usr/share/license/app-checker
 cp LICENSE ${D}/usr/share/license/app-checker-devel
 cp LICENSE ${D}/usr/share/license/app-checker-server
 cp LICENSE ${D}/usr/share/license/app-checker-server-devel
 
 
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
PACKAGES += " app-checker-server-dev "
PACKAGES += " app-checker-server "
PACKAGES += " app-checker "
PACKAGES += " app-checker-dev "

app-checker-server-dev_files = ""
app-checker-server-dev_files += "${prefix}/lib/libapp-checker-server.so"
app-checker-server-dev_files += "${prefix}/lib/pkgconfig/app-checker-server.pc"
app-checker-server-dev_files += "${prefix}/include/app-checker/app-checker-server.h"
app-checker-server-dev_files += "/usr/share/license/app-checker-server-devel"
MANIFESTFILES_${PN}-server-dev = "app-checker.manifest"

app-checker-server_files = ""
app-checker-server_files += "${prefix}/lib/libapp-checker-server.so.0"
app-checker-server_files += "${prefix}/lib/libapp-checker-server.so.0.1.0"
app-checker-server_files += "/usr/share/license/app-checker-server"
MANIFESTFILES_${PN}-server = "app-checker.manifest"

app-checker_files = ""
app-checker_files += "${prefix}/lib/libapp-checker.so.0"
app-checker_files += "${prefix}/lib/libapp-checker.so.0.1.0"
app-checker_files += "${prefix}/lib/ac-plugins"
app-checker_files += "/usr/share/license/app-checker"
MANIFESTFILES_${PN} = "app-checker.manifest"

app-checker-dev_files = ""
app-checker-dev_files += "${prefix}/lib/libapp-checker.so"
app-checker-dev_files += "${prefix}/lib/pkgconfig/app-checker.pc"
app-checker-dev_files += "${prefix}/include/app-checker/app-checker.h"
app-checker-dev_files += "/usr/share/license/app-checker-devel"
MANIFESTFILES_${PN}-dev = "app-checker.manifest"

FILES_${PN}-server-dev = "${app-checker-server-dev_files}"
FILES_${PN}-server = "${app-checker-server_files}"
FILES_${PN} = "${app-checker_files}"
FILES_${PN}-dev = "${app-checker-dev_files}"

PKG_app-checker-server-dev= "app-checker-server-dev"
PKG_app-checker-server= "app-checker-server"
PKG_app-checker= "app-checker"
PKG_app-checker-dev= "app-checker-dev"

require app-checker-extraconf.inc

