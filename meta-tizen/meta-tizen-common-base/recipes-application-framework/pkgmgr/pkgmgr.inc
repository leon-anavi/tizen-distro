DESCRIPTION = "Packager Manager client library package"
HOMEPAGE = "http://nohomepage.org"
SECTION = "Application Framework/Package Management"
LICENSE = "Apache-2.0"
PV = "0.2.89"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by pkgmgr-client
PROVIDES += "pkgmgr-client"


#PROVIDES by pkgmgr


#PROVIDES by pkgmgr-server
PROVIDES += "pkgmgr-server"


#PROVIDES by pkgmgr-types-dev
PROVIDES += "pkgmgr-types-dev"


#PROVIDES by pkgmgr-client-dev
PROVIDES += "pkgmgr-client-dev"


#PROVIDES by pkgmgr-installer-dev
PROVIDES += "pkgmgr-installer-dev"


#PROVIDES by pkgmgr-installer
PROVIDES += "pkgmgr-installer"


RDEPENDS = ""
#RDEPENDS of pkgmgr-client (${PN}-client)
RDEPENDS_${PN}-client += "shared-mime-info"
RDEPENDS_${PN}-client += "pkgmgr"

#RDEPENDS of pkgmgr-server (${PN}-server)
RDEPENDS_${PN}-server += "pkgmgr"

#RDEPENDS of pkgmgr-types-dev (${PN}-types-dev)
RDEPENDS_${PN}-types-dev += "pkgmgr"

#RDEPENDS of pkgmgr-client-dev (${PN}-client-dev)
RDEPENDS_${PN}-client-dev += "pkgmgr"

#RDEPENDS of pkgmgr-installer-dev (${PN}-installer-dev)
RDEPENDS_${PN}-installer-dev += "pkgmgr"

#RDEPENDS of pkgmgr-installer (${PN}-installer)
RDEPENDS_${PN}-installer += "pkgmgr"


DEPENDS = ""
#DEPENDS of pkgmgr
DEPENDS += "pkgmgr-info"
#Replace "DEPENDS" on gettext by "inherit gettext"
inherit gettext
DEPENDS += "unzip"
inherit tizen_cmake
DEPENDS += "iniparser"
DEPENDS += "notification"
DEPENDS += "dbus"
inherit pkgconfig
DEPENDS += "dlog"
DEPENDS += "security-server"
DEPENDS += "ail"
DEPENDS += "smack"
DEPENDS += "libslp-db-util"
DEPENDS += "bundle"
DEPENDS += "ecore"
DEPENDS += "app-core"
DEPENDS += "tizen-platform-config"
DEPENDS += "dbus-glib"
DEPENDS_append_class-native = " fdupes-native"
DEPENDS_append_class-target = " fdupes-native"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/pkgmgr.manifest ${S}/packaging/pkgmgr-client.manifest ${S}/packaging/pkgmgr-client-devel.manifest ${S}/packaging/pkgmgr-server.manifest ${S}/packaging/pkgmgr-installer.manifest ${S}/packaging/pkgmgr-installer-devel.manifest ${S}/packaging/pkgmgr-types-devel.manifest .
 
 
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
 rm -f  ${D}${prefix}/bin/pkgmgr_backend_sample
 rm -f ${D}${prefix}/lib/libpkgmgr_backend_lib_sample.so
 rm -f ${D}${prefix}/lib/libpkgmgr_parser_lib_sample.so
 
 mkdir -p ${D}${sysconfdir}/package-manager/backend
 mkdir -p ${D}${sysconfdir}/package-manager/backendlib
 mkdir -p ${D}${sysconfdir}/opt/upgrade
 
 mkdir -p ${D}${sysconfdir}/package-manager/server
 
 #find_lang package-manager
 
 #fdupes ${D}
 
 
}

pkg_postinst_pkgmgr-installer() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postinst_pkgmgr-server() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postinst_${PN}() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
    # For pkgmgr-install:
    # Update mime database to support package mime types
    update-mime-database $D${prefix}/share/mime
    chsmack -a '*' $D${prefix}/share/packages

}

pkg_postinst_pkgmgr-client() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_pkgmgr-client() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_pkgmgr-installer() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " pkgmgr-client "
PACKAGES += " pkgmgr "
PACKAGES += " pkgmgr-server "
PACKAGES += " pkgmgr-types-dev "
PACKAGES += " pkgmgr-client-dev "
PACKAGES += " pkgmgr-installer-dev "
PACKAGES += " pkgmgr-installer "

pkgmgr-client_files = ""
pkgmgr-client_files += "${sysconfdir}/package-manager"
pkgmgr-client_files += "${sysconfdir}/package-manager/pkg_path.conf"
pkgmgr-client_files += "${prefix}/lib/libpkgmgr-client.so.*"
CONFFILES_${PN}-client = ""
CONFFILES_${PN}-client += "${sysconfdir}/package-manager/pkg_path.conf"
MANIFESTFILES_${PN}-client = "pkgmgr-client.manifest"
DIRFILES_${PN}-client = ""
DIRFILES_${PN}-client += "${sysconfdir}/package-manager"

pkgmgr_files = ""
pkgmgr_files += "${sysconfdir}/package-manager/backend"
pkgmgr_files += "${sysconfdir}/package-manager/backendlib"
pkgmgr_files += "${sysconfdir}/opt/upgrade"
pkgmgr_files += "${sysconfdir}/opt/upgrade/pkgmgr.patch.sh"
pkgmgr_files += "${prefix}/bin/pkgcmd"
pkgmgr_files += "${prefix}/bin/pkg_createdb"
pkgmgr_files += "${prefix}/bin/pkg_createdb_user"
pkgmgr_files += "${prefix}/bin/pkg_syncdb"
pkgmgr_files += "${prefix}/bin/pkg_syncdb_user"
pkgmgr_files += "${prefix}/bin/pkg_initdb"
pkgmgr_files += "${prefix}/bin/pkg_initdb_user"
pkgmgr_files += "${prefix}/bin/pkg_getsize"
pkgmgr_files += "${prefix}/bin/pkg_clearcache"
pkgmgr_files += "${prefix}/bin/pkginfo"
pkgmgr_files += "${prefix}/bin/pkgmgr-install"
pkgmgr_files += "%dir ${prefix}/share/packages"
pkgmgr_files += "${prefix}/share/packages/org.tizen.pkgmgr-install.xml"
pkgmgr_files += "${prefix}/share/mime/packages/mime.wac.xml"
pkgmgr_files += "${prefix}/share/mime/packages/mime.tpk.xml"
MANIFESTFILES_${PN} = "pkgmgr.manifest"
DIRFILES_${PN} = ""
DIRFILES_${PN} += "${sysconfdir}/package-manager/backend"
DIRFILES_${PN} += "${sysconfdir}/package-manager/backendlib"
DIRFILES_${PN} += "${sysconfdir}/opt/upgrade"

pkgmgr-server_files = ""
pkgmgr-server_files += "${prefix}/share/dbus-1/system-services/org.tizen.slp.pkgmgr.service"
pkgmgr-server_files += "${sysconfdir}/dbus-1/system.d/org.tizen.slp.pkgmgr.conf"
pkgmgr-server_files += "${prefix}/bin/pkgmgr-server"
pkgmgr-server_files += "${sysconfdir}/package-manager/server"
CONFFILES_${PN}-server = ""
CONFFILES_${PN}-server += "${sysconfdir}/dbus-1/system.d/org.tizen.slp.pkgmgr.conf"
MANIFESTFILES_${PN}-server = "pkgmgr-server.manifest"

pkgmgr-types-dev_files = ""
pkgmgr-types-dev_files += "${prefix}/include/package-manager-types.h"
pkgmgr-types-dev_files += "${prefix}/include/package-manager-plugin.h"
pkgmgr-types-dev_files += "${prefix}/lib/pkgconfig/pkgmgr-types.pc"
MANIFESTFILES_${PN}-types-dev = "pkgmgr-types-devel.manifest"

pkgmgr-client-dev_files = ""
pkgmgr-client-dev_files += "${prefix}/include/package-manager.h"
pkgmgr-client-dev_files += "${prefix}/include/pkgmgr-dbinfo.h"
pkgmgr-client-dev_files += "${prefix}/lib/pkgconfig/pkgmgr.pc"
pkgmgr-client-dev_files += "${prefix}/lib/libpkgmgr-client.so"
MANIFESTFILES_${PN}-client-dev = "pkgmgr-client-devel.manifest"

pkgmgr-installer-dev_files = ""
pkgmgr-installer-dev_files += "${prefix}/include/pkgmgr"
pkgmgr-installer-dev_files += "${prefix}/include/pkgmgr/pkgmgr_installer.h"
pkgmgr-installer-dev_files += "${prefix}/lib/pkgconfig/pkgmgr-installer-status-broadcast-server.pc"
pkgmgr-installer-dev_files += "${prefix}/lib/pkgconfig/pkgmgr-installer.pc"
pkgmgr-installer-dev_files += "${prefix}/lib/pkgconfig/pkgmgr-installer-client.pc"
pkgmgr-installer-dev_files += "${prefix}/lib/libpkgmgr_installer.so"
pkgmgr-installer-dev_files += "${prefix}/lib/libpkgmgr_installer_client.so"
pkgmgr-installer-dev_files += "${prefix}/lib/libpkgmgr_installer_status_broadcast_server.so"
MANIFESTFILES_${PN}-installer-dev = "pkgmgr-installer-devel.manifest"
DIRFILES_${PN}-installer-dev = ""
DIRFILES_${PN}-installer-dev += "${prefix}/include/pkgmgr"

pkgmgr-installer_files = ""
pkgmgr-installer_files += "${prefix}/lib/libpkgmgr_installer.so.*"
pkgmgr-installer_files += "${prefix}/lib/libpkgmgr_installer_status_broadcast_server.so.*"
pkgmgr-installer_files += "${prefix}/lib/libpkgmgr_installer_client.so.*"
MANIFESTFILES_${PN}-installer = "pkgmgr-installer.manifest"

FILES_${PN}-client = "${pkgmgr-client_files}"
FILES_${PN} = "${pkgmgr_files}"
FILES_${PN}-server = "${pkgmgr-server_files}"
FILES_${PN}-types-dev = "${pkgmgr-types-dev_files}"
FILES_${PN}-client-dev = "${pkgmgr-client-dev_files}"
FILES_${PN}-installer-dev = "${pkgmgr-installer-dev_files}"
FILES_${PN}-installer = "${pkgmgr-installer_files}"

PKG_pkgmgr-client= "pkgmgr-client"
PKG_pkgmgr= "pkgmgr"
PKG_pkgmgr-server= "pkgmgr-server"
PKG_pkgmgr-types-dev= "pkgmgr-types-dev"
PKG_pkgmgr-client-dev= "pkgmgr-client-dev"
PKG_pkgmgr-installer-dev= "pkgmgr-installer-dev"
PKG_pkgmgr-installer= "pkgmgr-installer"

require pkgmgr-extraconf.inc

