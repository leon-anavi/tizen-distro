DESCRIPTION = "Security manager and utilities"
HOMEPAGE = "http://nohomepage.org"
SECTION = "Security/Service"
LICENSE = "Apache-2.0"
PV = "0.2.0"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by security-manager


#PROVIDES by libsecurity-manager-client
PROVIDES += "libsecurity-manager-client"


#PROVIDES by libsecurity-manager-client-dev
PROVIDES += "libsecurity-manager-client-dev"


RDEPENDS = ""
#RDEPENDS of security-manager (${PN})
RDEPENDS_${PN} += "smack"
RDEPENDS_${PN} += "systemd"

#RDEPENDS of libsecurity-manager-client (lib${PN}-client)
RDEPENDS_lib${PN}-client += "security-manager"
RDEPENDS_lib${PN}-client += "glibc"

#RDEPENDS of libsecurity-manager-client-dev (lib${PN}-client-dev)
RDEPENDS_lib${PN}-client-dev += "libsecurity-manager-client"


DEPENDS = ""
#DEPENDS of security-manager
DEPENDS += "systemd"
inherit tizen_cmake
DEPENDS += "attr"
DEPENDS += "zip"
DEPENDS += "boost"
DEPENDS += "tizen-platform-config"
inherit pkgconfig
DEPENDS += "smack"
DEPENDS += "pkgconfig(cynara-client)"
DEPENDS += "sqlite3"
DEPENDS += "libcap"
DEPENDS += "pkgconfig(cynara-admin)"
DEPENDS += "libslp-db-util"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/security-manager.manifest .
 cp ${S}/packaging/libsecurity-manager-client.manifest .
 
 
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
 
 
 export LDFLAGS+="-Wl,--rpath=${prefix}/lib"
 
 
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
         ${EXTRA_OECMAKE} . -DVERSION=0.2.0 \
         -DBIN_INSTALL_DIR=${prefix}/bin \
         -DDB_INSTALL_DIR=${prefix}/dbspace \
         -DSYSTEMD_INSTALL_DIR=${systemd_unitdir}/system \
         -DCMAKE_BUILD_TYPE=RELEASE \
         -DCMAKE_VERBOSE_MAKEFILE=ON
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
 mkdir -p ${D}/usr/share/license
 cp LICENSE ${D}/usr/share/license/security-manager
 cp LICENSE ${D}/usr/share/license/libsecurity-manager-client
 mkdir -p ${D}/${sysconfdir}/smack
 cp app-rules-template.smack ${D}/${sysconfdir}/smack
 
   oe_runmake \
         DESTDIR=${D} \
         INSTALL_ROOT=${D} \
         BINDIR=${prefix}/bin \
   install  
   rm -f ${D}${infodir}/dir 
   find ${D} -regex ".*\.la$" | xargs rm -f -- 
   find ${D} -regex ".*\.a$" | xargs rm -f --
 
 mkdir -p ${D}/${systemd_unitdir}/system/multi-user.target.wants
 mkdir -p ${D}/${systemd_unitdir}/system/sockets.target.wants
 ln -s ../security-manager.service ${D}/${systemd_unitdir}/system/multi-user.target.wants/security-manager.service
 ln -s ../security-manager.socket ${D}/${systemd_unitdir}/system/sockets.target.wants/security-manager.socket
 
 
}

pkg_postinst_libsecurity-manager-client() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postinst_${PN}() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
    systemctl daemon-reload
    if [ $1 = 1 ]; then
        # installation
        systemctl start security-manager.service
    fi
    if [ $1 = 2 ]; then
        # update
        systemctl restart security-manager.service
    fi
    chsmack -a System $D${prefix}/dbspace/.security-manager.db
    chsmack -a System $D${prefix}/dbspace/.security-manager.db-journal

}

pkg_prerm_${PN}() {
    #!/bin/sh -e

    if [ $1 = 0 ]; then
        # unistall
        systemctl stop security-manager.service
    fi

}

pkg_postrm_libsecurity-manager-client() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_${PN}() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
    if [ $1 = 0 ]; then
        # unistall
        systemctl daemon-reload
    fi

}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " security-manager "
PACKAGES += " libsecurity-manager-client "
PACKAGES += " libsecurity-manager-client-dev "

security-manager_files = ""
security-manager_files += "${prefix}/bin/security-manager"
security-manager_files += "${prefix}/lib/libsecurity-manager-commons.so.*"
security-manager_files += "${systemd_unitdir}/system/multi-user.target.wants/security-manager.service"
security-manager_files += "${systemd_unitdir}/system/security-manager.service"
security-manager_files += "${systemd_unitdir}/system/security-manager.target"
security-manager_files += "${systemd_unitdir}/system/sockets.target.wants/security-manager.socket"
security-manager_files += "${systemd_unitdir}/system/security-manager.socket"
security-manager_files += "${sysconfdir}/smack/app-rules-template.smack"
security-manager_files += "%attr(0600,root,root) ${prefix}/dbspace/.security-manager.db"
security-manager_files += "%attr(0600,root,root) ${prefix}/dbspace/.security-manager.db-journal"
security-manager_files += "${prefix}/share/license/security-manager"
MANIFESTFILES_${PN} = "security-manager.manifest"

libsecurity-manager-client_files = ""
libsecurity-manager-client_files += "${prefix}/lib/libsecurity-manager-client.so.*"
libsecurity-manager-client_files += "${prefix}/share/license/libsecurity-manager-client"
MANIFESTFILES_lib${PN}-client = "libsecurity-manager-client.manifest"

libsecurity-manager-client-dev_files = ""
libsecurity-manager-client-dev_files += "${prefix}/lib/libsecurity-manager-client.so"
libsecurity-manager-client-dev_files += "${prefix}/lib/libsecurity-manager-commons.so"
libsecurity-manager-client-dev_files += "${prefix}/include/security-manager/security-manager.h"
libsecurity-manager-client-dev_files += "${prefix}/lib/pkgconfig/security-manager.pc"
MANIFESTFILES_lib${PN}-client-dev = "security-manager.manifest"

FILES_${PN} = "${security-manager_files}"
FILES_lib${PN}-client = "${libsecurity-manager-client_files}"
FILES_lib${PN}-client-dev = "${libsecurity-manager-client-dev_files}"

PKG_security-manager= "security-manager"
PKG_libsecurity-manager-client= "libsecurity-manager-client"
PKG_libsecurity-manager-client-dev= "libsecurity-manager-client-dev"

require security-manager-extraconf.inc

