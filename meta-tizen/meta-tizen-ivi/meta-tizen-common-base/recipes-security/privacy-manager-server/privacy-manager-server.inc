DESCRIPTION = "Privacy Management"
HOMEPAGE = "http://nohomepage.org"
SECTION = "Security/Libraries"
LICENSE = "Apache-2.0"
PV = "0.0.4"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by privacy-manager-client
PROVIDES += "privacy-manager-client"


#PROVIDES by privacy-manager-server


#PROVIDES by privacy-manager-server-dev
PROVIDES += "privacy-manager-server-dev"


#PROVIDES by capi-security-privacy-manager
PROVIDES += "capi-security-privacy-manager"


#PROVIDES by privacy-manager-client-dev
PROVIDES += "privacy-manager-client-dev"


#PROVIDES by capi-security-privacy-manager-dev
PROVIDES += "capi-security-privacy-manager-dev"


RDEPENDS = ""
#RDEPENDS of privacy-manager-client (privacy-manager-client)
RDEPENDS_privacy-manager-client += "privacy-manager-server"

#RDEPENDS of privacy-manager-server (${PN})
RDEPENDS_${PN} += "glibc"

#RDEPENDS of privacy-manager-server-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "privacy-manager-server"

#RDEPENDS of capi-security-privacy-manager (capi-security-privacy-manager)
RDEPENDS_capi-security-privacy-manager += "privacy-manager-client"

#RDEPENDS of privacy-manager-client-dev (privacy-manager-client-dev)
RDEPENDS_privacy-manager-client-dev += "privacy-manager-client"

#RDEPENDS of capi-security-privacy-manager-dev (capi-security-privacy-manager-dev)
RDEPENDS_capi-security-privacy-manager-dev += "capi-security-privacy-manager"


DEPENDS = ""
#DEPENDS of privacy-manager-server
DEPENDS += "pkgmgr-info"
#Replace "DEPENDS" on gettext by "inherit gettext"
inherit gettext
inherit tizen_cmake
DEPENDS += "capi-system-info"
DEPENDS += "dbus-glib"
DEPENDS += "libxml2"
DEPENDS += "dbus"
inherit pkgconfig
DEPENDS += "dlog"
DEPENDS += "glib-2.0"
DEPENDS += "capi-base-common"
DEPENDS += "sqlite3"
DEPENDS += "tizen-platform-config"
DEPENDS += "libslp-db-util"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/privacy-manager-server.manifest .
 cp ${S}/packaging/privacy-manager-server-devel.manifest .
 cp ${S}/packaging/privacy-manager-client.manifest .
 cp ${S}/packaging/privacy-manager-client-devel.manifest .
 cp ${S}/packaging/capi-security-privacy-manager.manifest .
 cp ${S}/packaging/capi-security-privacy-manager-devel.manifest .
 
 
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
         ${EXTRA_OECMAKE} . -DPREFIX=${prefix} \
         -DEXEC_PREFIX=${prefix} \
         -DLIBDIR=${prefix}/lib \
         -DINCLUDEDIR=${prefix}/include \
         -DCMAKE_BUILD_TYPE="Release" \
         -DVERSION=0.0.4 \
         -DFILTER_LISTED_PKG=ON \
         -DPRIVACY_POPUP=OFF
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
 
 mkdir -p ${D}${prefix}/bin
 cp res/usr/bin/* ${D}${prefix}/bin/
 mkdir -p ${D}${prefix}/dbspace
 cp res/opt/dbspace/.privacylist.db /${D}${prefix}/dbspace
 mkdir -p ${D}${prefix}/share/privacy-manager/
 cp res/usr/share/privacy-manager/privacy-filter-list.ini ${D}${prefix}/share/privacy-manager/
 
 
   oe_runmake \
         DESTDIR=${D} \
         INSTALL_ROOT=${D} \
         BINDIR=${prefix}/bin \
   install  
   rm -f ${D}${infodir}/dir 
   find ${D} -regex ".*\.la$" | xargs rm -f -- 
   find ${D} -regex ".*\.a$" | xargs rm -f --
 
 #mkdir -p %{buildroot}%{_libdir}/systemd/system/multi-user.target.wants
 #install -m 0644 %{SOURCE1} %{buildroot}%{_libdir}/systemd/system/privacy-manager-server.service
 #ln -sf /usr/lib/systemd/system/privacy-manager-server.service %{buildroot}%{_libdir}/systemd/system/multi-user.target.wants/privacy-manager-server.service
 
 
 
}

pkg_postinst_privacy-manager-client() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postinst_privacy-manager-server() {
    #!/bin/sh -e

    ldconfig
    echo "Check privacy DB"
    if [ ! -f $D${prefix}/dbspace/.privacy.db ]
    then
    	echo "Create privacy DB"
    	privacy_manager_create_clean_db.sh
    fi
    chsmack -a 'User' $D${prefix}/dbspace/.privacy.db*
    chsmack -a 'User' $D${prefix}/dbspace/.privacylist.db*

}

pkg_postinst_capi-security-privacy-manager() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_${PN}() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_capi-security-privacy-manager() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_privacy-manager-client() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " privacy-manager-client "
PACKAGES += " privacy-manager-server "
PACKAGES += " privacy-manager-server-dev "
PACKAGES += " capi-security-privacy-manager "
PACKAGES += " privacy-manager-client-dev "
PACKAGES += " capi-security-privacy-manager-dev "

privacy-manager-client_files = ""
privacy-manager-client_files += "${prefix}/lib/libprivacy-manager-client.so*"
privacy-manager-client_files += "${prefix}/share/privacy-manager/privacy-filter-list.ini"
privacy-manager-client_files += "${sysconfdir}/package-manager/parserlib/libprivileges.so"
MANIFESTFILES_privacy-manager-client = "privacy-manager-client.manifest"

privacy-manager-server_files = ""
privacy-manager-server_files += "${prefix}/lib/libprivacy-manager-server.so*"
privacy-manager-server_files += "${prefix}/dbspace/.privacylist.db"
privacy-manager-server_files += "${prefix}/bin/*"
MANIFESTFILES_${PN} = "privacy-manager-server.manifest"

privacy-manager-server-dev_files = ""
privacy-manager-server-dev_files += "${prefix}/include/privacy_manager/server/privacy_manager_daemon.h"
privacy-manager-server-dev_files += "${prefix}/lib/pkgconfig/privacy-manager-server.pc"

capi-security-privacy-manager_files = ""
capi-security-privacy-manager_files += "${prefix}/lib/libcapi-security-privacy-manager.so.*"
MANIFESTFILES_capi-security-privacy-manager = "capi-security-privacy-manager.manifest"

privacy-manager-client-dev_files = ""
privacy-manager-client-dev_files += "${prefix}/include/*"
privacy-manager-client-dev_files += "${prefix}/lib/pkgconfig/privacy-manager-client.pc"
MANIFESTFILES_privacy-manager-client-dev = "privacy-manager-client-devel.manifest"

capi-security-privacy-manager-dev_files = ""
capi-security-privacy-manager-dev_files += "${prefix}/include/privacymgr/*.h"
capi-security-privacy-manager-dev_files += "${prefix}/lib/libcapi-security-privacy-manager.so"
capi-security-privacy-manager-dev_files += "${prefix}/lib/pkgconfig/capi-security-privacy-manager.pc"
MANIFESTFILES_capi-security-privacy-manager-dev = "capi-security-privacy-manager-devel.manifest"

FILES_privacy-manager-client = "${privacy-manager-client_files}"
FILES_${PN} = "${privacy-manager-server_files}"
FILES_${PN}-dev = "${privacy-manager-server-dev_files}"
FILES_capi-security-privacy-manager = "${capi-security-privacy-manager_files}"
FILES_privacy-manager-client-dev = "${privacy-manager-client-dev_files}"
FILES_capi-security-privacy-manager-dev = "${capi-security-privacy-manager-dev_files}"

PKG_privacy-manager-client= "privacy-manager-client"
PKG_privacy-manager-server= "privacy-manager-server"
PKG_privacy-manager-server-dev= "privacy-manager-server-dev"
PKG_capi-security-privacy-manager= "capi-security-privacy-manager"
PKG_privacy-manager-client-dev= "privacy-manager-client-dev"
PKG_capi-security-privacy-manager-dev= "capi-security-privacy-manager-dev"

require privacy-manager-server-extraconf.inc

