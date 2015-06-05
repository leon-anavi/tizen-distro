DESCRIPTION = "Application Service"
HOMEPAGE = "http://nohomepage.org"
SECTION = "Application Framework/Service"
LICENSE = "Apache-2.0"
PV = "0.1.53"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by app-svc


#PROVIDES by app-svc-dev
PROVIDES += "app-svc-dev"


RDEPENDS = ""
#RDEPENDS of app-svc (${PN})
RDEPENDS_${PN} += "glibc"

#RDEPENDS of app-svc-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "app-svc"


DEPENDS = ""
#DEPENDS of app-svc
DEPENDS += "pkgmgr-info"
DEPENDS += "libsoup-2.4"
inherit tizen_cmake
DEPENDS += "iniparser"
DEPENDS += "tizen-platform-config"
inherit pkgconfig
DEPENDS += "dlog"
DEPENDS += "aul"
DEPENDS += "xdgmime"
DEPENDS += "ail"
DEPENDS += "bundle"
DEPENDS += "sqlite3"
DEPENDS += "ecore"
DEPENDS += "libprivilege-control"
DEPENDS += "glib-2.0"
DEPENDS += "dbus-glib"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 sed -i ${S}/packaging/app-svc.manifest -e "s|TZ_SYS_DB|${prefix}/dbspace|g"
 cp ${S}/packaging/app-svc.manifest .
 
 
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
         ${EXTRA_OECMAKE} . \
 -Dwith_wayland=TRUE
 
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
 
 # Create database
 mkdir -p ${D}${prefix}/dbspace
 sqlite3 ${D}${prefix}/dbspace/.appsvc.db < data/appsvc_db.sql
 
 
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
PACKAGES += " app-svc "
PACKAGES += " app-svc-dev "

app-svc_files = ""
app-svc_files += "%verify(not md5 mtime size) %attr(664,root,users) ${prefix}/dbspace/.appsvc.db"
app-svc_files += "%verify(not md5 mtime size) %attr(664,root,users) ${prefix}/dbspace/.appsvc.db-journal"
app-svc_files += "${prefix}/bin/appsvc_test"
app-svc_files += "${prefix}/lib/libappsvc.so.0"
app-svc_files += "${prefix}/lib/libappsvc.so.0.1.0"
MANIFESTFILES_${PN} = "app-svc.manifest"

app-svc-dev_files = ""
app-svc-dev_files += "${prefix}/lib/pkgconfig/appsvc.pc"
app-svc-dev_files += "${prefix}/lib/libappsvc.so"
app-svc-dev_files += "${prefix}/include/appsvc/appsvc.h"
MANIFESTFILES_${PN}-dev = "app-svc.manifest"

FILES_${PN} = "${app-svc_files}"
FILES_${PN}-dev = "${app-svc-dev_files}"

PKG_app-svc= "app-svc"
PKG_app-svc-dev= "app-svc-dev"

require app-svc-extraconf.inc

