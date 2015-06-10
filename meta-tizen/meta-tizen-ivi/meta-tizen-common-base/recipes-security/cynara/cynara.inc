DESCRIPTION = "Cynara service with client libraries"
HOMEPAGE = "http://nohomepage.org"
SECTION = "Security/Application Privilege"
LICENSE = "Apache-2.0"
PV = "0.5.0"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by libcynara-creds-socket
PROVIDES += "libcynara-creds-socket"


#PROVIDES by cynara-tests
PROVIDES += "cynara-tests"


#PROVIDES by libcynara-client
PROVIDES += "libcynara-client"


#PROVIDES by libcynara-creds-dbus
PROVIDES += "libcynara-creds-dbus"


#PROVIDES by cynara


#PROVIDES by cynara-dev
PROVIDES += "cynara-dev"


#PROVIDES by cyad
PROVIDES += "cyad"


#PROVIDES by libcynara-commons
PROVIDES += "libcynara-commons"


#PROVIDES by libcynara-admin
PROVIDES += "libcynara-admin"


#PROVIDES by libcynara-creds-commons
PROVIDES += "libcynara-creds-commons"


#PROVIDES by cynara-db-migration
PROVIDES += "cynara-db-migration"


#PROVIDES by libcynara-agent
PROVIDES += "libcynara-agent"


#PROVIDES by libcynara-session
PROVIDES += "libcynara-session"


RDEPENDS = ""
#RDEPENDS of cynara (${PN})
RDEPENDS_${PN} += "systemd"
RDEPENDS_${PN} += "default-ac-domains"
RDEPENDS_${PN} += "cynara-db-migration"
RDEPENDS_${PN} += "smack"
RDEPENDS_${PN} += "shadow"

#RDEPENDS of libcynara-client (lib${PN}-client)
RDEPENDS_lib${PN}-client += "cynara"

#RDEPENDS of libcynara-creds-dbus (lib${PN}-creds-dbus)
RDEPENDS_lib${PN}-creds-dbus += "dbus"

#RDEPENDS of cynara-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "systemd"
RDEPENDS_${PN}-dev += "libcynara-client"
RDEPENDS_${PN}-dev += "dbus"
RDEPENDS_${PN}-dev += "libcynara-creds-dbus"
RDEPENDS_${PN}-dev += "libcynara-creds-commons"
RDEPENDS_${PN}-dev += "libcynara-commons"
RDEPENDS_${PN}-dev += "libcynara-admin"
RDEPENDS_${PN}-dev += "libcynara-creds-socket"
RDEPENDS_${PN}-dev += "libcynara-agent"
RDEPENDS_${PN}-dev += "libcynara-session"

#RDEPENDS of libcynara-admin (lib${PN}-admin)
RDEPENDS_lib${PN}-admin += "cynara"

#RDEPENDS of libcynara-agent (lib${PN}-agent)
RDEPENDS_lib${PN}-agent += "cynara"


DEPENDS = ""
#DEPENDS of cynara-tests
#DEPENDS of cynara
#DEPENDS of libcynara-creds-dbus
DEPENDS += "systemd"
inherit tizen_cmake
DEPENDS += "zip"
DEPENDS += "dbus"
inherit pkgconfig
DEPENDS += "pkgconfig(gmock)"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp -a ${S}/packaging/cynara.manifest .
 cp -a ${S}/packaging/libcynara-client.manifest .
 cp -a ${S}/packaging/libcynara-admin.manifest .
 cp -a ${S}/packaging/cynara-tests.manifest .
 cp -a ${S}/packaging/libcynara-agent.manifest .
 cp -a ${S}/packaging/libcynara-commons.manifest .
 cp -a ${S}/packaging/libcynara-creds-commons.manifest .
 cp -a ${S}/packaging/libcynara-creds-dbus.manifest .
 cp -a ${S}/packaging/libcynara-creds-socket.manifest .
 cp -a ${S}/packaging/libcynara-session.manifest .
 cp -a ${S}/packaging/cynara-db-migration.manifest .
 cp -a ${S}/packaging/cyad.manifest .
 cp -a test/db/db* .
 
 
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
 
 
 
 export CXXFLAGS="$CXXFLAGS -DCYNARA_STATE_PATH=\\\"${localstatedir}/cynara/\\\" \
                            -DCYNARA_LIB_PATH=\\\"${prefix}/lib/cynara/\\\" \
                            -DCYNARA_TESTS_DIR=\\\"${prefix}/share/cynara/tests/\\\" \
                            -DCYNARA_CONFIGURATION_DIR=\\\"${sysconfdir}/cynara/\\\""
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
         ${EXTRA_OECMAKE} . \
         -DBUILD_TESTS=ON \
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
 
   oe_runmake \
         DESTDIR=${D} \
         INSTALL_ROOT=${D} \
         BINDIR=${prefix}/bin \
   install  
   rm -f ${D}${infodir}/dir 
   find ${D} -regex ".*\.la$" | xargs rm -f -- 
   find ${D} -regex ".*\.a$" | xargs rm -f --
 
 mkdir -p ${D}/${sysconfdir}/cynara/
 cp ./conf/creds.conf ${D}/${sysconfdir}/cynara//creds.conf
 
 mkdir -p ${D}/usr/lib/systemd/system/sockets.target.wants
 mkdir -p ${D}/${localstatedir}/cynara/
 mkdir -p ${D}${prefix}/share/cynara/tests//empty_db
 mkdir -p ${D}${prefix}/lib/cynara//plugin/client
 mkdir -p ${D}${prefix}/lib/cynara//plugin/service
 
 cp -a db* ${D}${prefix}/share/cynara/tests/
 ln -s ../cynara.socket ${D}/usr/lib/systemd/system/sockets.target.wants/cynara.socket
 ln -s ../cynara-admin.socket ${D}/usr/lib/systemd/system/sockets.target.wants/cynara-admin.socket
 ln -s ../cynara-agent.socket ${D}/usr/lib/systemd/system/sockets.target.wants/cynara-agent.socket
 
 
}

pkg_preinst_${PN}() {
    #!/bin/sh -e

    id -g cynara > /dev/null 2>&1
    if [ $? -eq 1 ]; then
        groupadd cynara -r > /dev/null 2>&1
    fi
    id -u cynara > /dev/null 2>&1
    if [ $? -eq 1 ]; then
        useradd -d /var/lib/empty -s /sbin/nologin -r -g cynara cynara > /dev/null 2>&1
    fi
    if [ $1 -gt 1 ] ; then
        OLDVERSION="$(rpm -q --qf '%{version}' cynara)"
        $D${prefix}/sbin/cynara/cynara-db-migration.sh upgrade -f ${OLDVERSION} -t 0.5.0
    else
        $D${prefix}/sbin/cynara/cynara-db-migration.sh install -t 0.5.0
    fi

}

pkg_postinst_libcynara-agent() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postinst_${PN}() {
    #!/bin/sh -e

    ### Add file capabilities if needed
    ### setcap/getcap binary are useful. To use them you must install libcap and libcap-tools packages
    ### In such case uncomment Requires with those packages
    systemctl daemon-reload
    if [ $1 = 1 ]; then
        systemctl enable cynara.service
    fi
    chsmack -a System ${localstatedir}/cynara/
    systemctl restart cynara.service

}

pkg_postinst_libcynara-creds-socket() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postinst_libcynara-client() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postinst_libcynara-creds-dbus() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postinst_libcynara-session() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postinst_libcynara-admin() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postinst_libcynara-creds-commons() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postinst_libcynara-commons() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_prerm_${PN}() {
    #!/bin/sh -e

    if [ $1 = 0 ]; then
        # unistall
        systemctl stop cynara.service
    fi

}

pkg_postrm_libcynara-creds-commons() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_libcynara-creds-socket() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_libcynara-agent() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_libcynara-admin() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_${PN}() {
    #!/bin/sh -e

    if [ $1 = 0 ]; then
        $D${prefix}/sbin/cynara/cynara-db-migration.sh uninstall -f 0.5.0
        userdel -r cynara > /dev/null 2>&1
        groupdel cynara > /dev/null 2>&1
        systemctl daemon-reload
    fi

}

pkg_postrm_libcynara-creds-dbus() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_libcynara-session() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_libcynara-client() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_libcynara-commons() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " cynara-tests "
PACKAGES += " libcynara-client "
PACKAGES += " libcynara-creds-dbus "
PACKAGES += " cynara-db-migration "
PACKAGES += " cynara-dev "
PACKAGES += " cyad "
PACKAGES += " cynara "
PACKAGES += " libcynara-commons "
PACKAGES += " libcynara-admin "
PACKAGES += " libcynara-creds-commons "
PACKAGES += " libcynara-creds-socket "
PACKAGES += " libcynara-agent "
PACKAGES += " libcynara-session "

cynara-tests_files = ""
cynara-tests_files += "/usr/bin/cynara-tests"
cynara-tests_files += "${prefix}/share/cynara/tests/db*/*"
cynara-tests_files += "%attr(755,root,root) ${prefix}/share/cynara/tests/empty_db"
MANIFESTFILES_${PN}-tests = "cynara-tests.manifest"
DIRFILES_${PN}-tests = ""
DIRFILES_${PN}-tests += "%attr(755,root,root) ${prefix}/share/cynara/tests/empty_db"

libcynara-client_files = ""
libcynara-client_files += "${prefix}/lib/libcynara-client.so.*"
libcynara-client_files += "${prefix}/lib/libcynara-client-async.so.*"
libcynara-client_files += "${prefix}/lib/libcynara-client-commons.so.*"
libcynara-client_files += "%attr(755,cynara,cynara) ${prefix}/lib/cynara/plugin/client"
MANIFESTFILES_lib${PN}-client = "libcynara-client.manifest"
DIRFILES_lib${PN}-client = ""
DIRFILES_lib${PN}-client += "%attr(755,cynara,cynara) ${prefix}/lib/cynara/plugin/client"

libcynara-creds-dbus_files = ""
libcynara-creds-dbus_files += "${prefix}/lib/libcynara-creds-dbus.so.*"
MANIFESTFILES_lib${PN}-creds-dbus = "libcynara-creds-dbus.manifest"

cynara-db-migration_files = ""
cynara-db-migration_files += "${prefix}/sbin/cynara/cynara-db-migration.sh"
MANIFESTFILES_${PN}-db-migration = "cynara-db-migration.manifest"

cynara-dev_files = ""
cynara-dev_files += "${prefix}/include/cynara/*.h"
cynara-dev_files += "${prefix}/include/cynara/log/*.h"
cynara-dev_files += "${prefix}/include/cynara/plugin/*.h"
cynara-dev_files += "${prefix}/include/cynara/types/*.h"
cynara-dev_files += "${prefix}/lib/pkgconfig/*.pc"
cynara-dev_files += "${prefix}/lib/*.so"

cyad_files = ""
cyad_files += "${prefix}/sbin/cyad"
MANIFESTFILES_cyad = "cyad.manifest"

cynara_files = ""
cynara_files += "/usr/bin/cynara"
cynara_files += "/usr/lib/systemd/system/cynara.service"
cynara_files += "/usr/lib/systemd/system/cynara.target"
cynara_files += "/usr/lib/systemd/system/sockets.target.wants/cynara.socket"
cynara_files += "/usr/lib/systemd/system/cynara.socket"
cynara_files += "/usr/lib/systemd/system/sockets.target.wants/cynara-admin.socket"
cynara_files += "/usr/lib/systemd/system/cynara-admin.socket"
cynara_files += "/usr/lib/systemd/system/sockets.target.wants/cynara-agent.socket"
cynara_files += "/usr/lib/systemd/system/cynara-agent.socket"
cynara_files += "%attr(700,cynara,cynara) ${localstatedir}/cynara/"
cynara_files += "%attr(755,cynara,cynara) ${prefix}/lib/cynara/plugin/service"
MANIFESTFILES_${PN} = "cynara.manifest"
DIRFILES_${PN} = ""
DIRFILES_${PN} += "%attr(700,cynara,cynara) ${localstatedir}/cynara/"
DIRFILES_${PN} += "%attr(755,cynara,cynara) ${prefix}/lib/cynara/plugin/service"

libcynara-commons_files = ""
libcynara-commons_files += "${prefix}/lib/libcynara-commons.so.*"
libcynara-commons_files += "${prefix}/lib/libcynara-storage.so.*"
MANIFESTFILES_lib${PN}-commons = "libcynara-commons.manifest"

libcynara-admin_files = ""
libcynara-admin_files += "${prefix}/lib/libcynara-admin.so.*"
MANIFESTFILES_lib${PN}-admin = "libcynara-admin.manifest"

libcynara-creds-commons_files = ""
libcynara-creds-commons_files += "${prefix}/lib/libcynara-creds-commons.so.*"
libcynara-creds-commons_files += "${sysconfdir}/cynara/creds.conf"
MANIFESTFILES_lib${PN}-creds-commons = "libcynara-creds-commons.manifest"

libcynara-creds-socket_files = ""
libcynara-creds-socket_files += "${prefix}/lib/libcynara-creds-socket.so.*"
MANIFESTFILES_lib${PN}-creds-socket = "libcynara-creds-socket.manifest"

libcynara-agent_files = ""
libcynara-agent_files += "${prefix}/lib/libcynara-agent.so.*"
MANIFESTFILES_lib${PN}-agent = "libcynara-agent.manifest"

libcynara-session_files = ""
libcynara-session_files += "${prefix}/lib/libcynara-session.so.*"
MANIFESTFILES_lib${PN}-session = "libcynara-session.manifest"

FILES_${PN}-tests = "${cynara-tests_files}"
FILES_lib${PN}-client = "${libcynara-client_files}"
FILES_lib${PN}-creds-dbus = "${libcynara-creds-dbus_files}"
FILES_${PN}-db-migration = "${cynara-db-migration_files}"
FILES_${PN}-dev = "${cynara-dev_files}"
FILES_cyad = "${cyad_files}"
FILES_${PN} = "${cynara_files}"
FILES_lib${PN}-commons = "${libcynara-commons_files}"
FILES_lib${PN}-admin = "${libcynara-admin_files}"
FILES_lib${PN}-creds-commons = "${libcynara-creds-commons_files}"
FILES_lib${PN}-creds-socket = "${libcynara-creds-socket_files}"
FILES_lib${PN}-agent = "${libcynara-agent_files}"
FILES_lib${PN}-session = "${libcynara-session_files}"

PKG_cynara-tests= "cynara-tests"
PKG_libcynara-client= "libcynara-client"
PKG_libcynara-creds-dbus= "libcynara-creds-dbus"
PKG_cynara-db-migration= "cynara-db-migration"
PKG_cynara-dev= "cynara-dev"
PKG_cyad= "cyad"
PKG_cynara= "cynara"
PKG_libcynara-commons= "libcynara-commons"
PKG_libcynara-admin= "libcynara-admin"
PKG_libcynara-creds-commons= "libcynara-creds-commons"
PKG_libcynara-creds-socket= "libcynara-creds-socket"
PKG_libcynara-agent= "libcynara-agent"
PKG_libcynara-session= "libcynara-session"

require cynara-extraconf.inc

