DESCRIPTION = "App utility library"
HOMEPAGE = "http://nohomepage.org"
SECTION = "System/Libraries"
LICENSE = "Apache-2.0"
PV = "0.0.300"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by aul


#PROVIDES by aul-dev
PROVIDES += "aul-dev"


#PROVIDES by aul-test
PROVIDES += "aul-test"


RDEPENDS = ""
#RDEPENDS of aul (${PN})
RDEPENDS_${PN} += "glibc"
RDEPENDS_${PN} += "systemd"

#RDEPENDS of aul-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "aul"

#RDEPENDS of aul-test (${PN}-test)
RDEPENDS_${PN}-test += "aul"


DEPENDS = ""
#DEPENDS of aul
DEPENDS += "pkgmgr-info"
DEPENDS += "librua"
inherit tizen_cmake
DEPENDS += "attr"
DEPENDS += "tizen-platform-config"
DEPENDS += "privacy-manager-server"
inherit pkgconfig
DEPENDS += "bundle"
DEPENDS += "ail"
DEPENDS += "smack"
DEPENDS += "dlog"
DEPENDS += "sqlite3"
DEPENDS += "xdgmime"
DEPENDS += "libprivilege-control"
DEPENDS += "app-checker"
DEPENDS += "vconf"
DEPENDS += "dbus-glib"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 sed -i 's|TZ_SYS_DB|${prefix}/dbspace|g' ${S}/packaging/aul.manifest
 cp ${S}/packaging/aul.manifest .
 
 
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
 
 rm -rf ${D}
 
   oe_runmake \
         DESTDIR=${D} \
         INSTALL_ROOT=${D} \
         BINDIR=${prefix}/bin \
   install  
   rm -f ${D}${infodir}/dir 
   find ${D} -regex ".*\.la$" | xargs rm -f -- 
   find ${D} -regex ".*\.a$" | xargs rm -f --
 
 mkdir -p ${D}${sysconfdir}/init.d
 install -m 755 launchpad_run ${D}${sysconfdir}/init.d
 
 mkdir -p ${D}${sysconfdir}/rc.d/rc3.d
 mkdir -p ${D}${sysconfdir}/rc.d/rc4.d
 ln -sf ../../init.d/launchpad_run ${D}/${sysconfdir}/rc.d/rc3.d/S34launchpad_run
 ln -sf ../../init.d/launchpad_run ${D}/${sysconfdir}/rc.d/rc4.d/S80launchpad_run
 
 mkdir -p ${D}${prefix}/dbspace
 sqlite3 ${D}${prefix}/dbspace/.mida.db < ${D}${prefix}/share/aul/mida_db.sql
 rm -rf ${D}${prefix}/share/aul/mida_db.sql
 
 mkdir -p ${D}${systemd_unitdir}/system
 mkdir -p ${D}${prefix}/lib/systemd/user
 install -m 0644 ${S}/packaging/ac.service ${D}${systemd_unitdir}/system/ac.service
 install -m 0644 ${S}/packaging/amd_session_agent.service ${D}${prefix}/lib/systemd/user/amd_session_agent.service
 
 
}

pkg_postinst_${PN}() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
    systemctl enable ac
    systemctl --global enable amd_session_agent
    systemctl daemon-reload
    if [ $1 == 1 ]; then
        systemctl restart ac.service
    fi

}

pkg_prerm_${PN}() {
    #!/bin/sh -e

    if [ $1 == 0 ]; then
        systemctl stop ac.service
        systemctl disable ac
        systemctl --global disable amd_session_agent
    fi

}

pkg_postrm_${PN}() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
    systemctl daemon-reload

}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " aul "
PACKAGES += " aul-dev "
PACKAGES += " aul-test "

aul_files = ""
aul_files += "${prefix}/lib/libaul.so.0"
aul_files += "${prefix}/lib/libaul.so.0.1.0"
aul_files += "${sysconfdir}/init.d/launchpad_run"
aul_files += "${sysconfdir}/rc.d/rc3.d/S34launchpad_run"
aul_files += "${sysconfdir}/rc.d/rc4.d/S80launchpad_run"
aul_files += "%attr(0644,root,users) ${prefix}/dbspace/.mida.db"
aul_files += "%attr(0644,root,users) ${prefix}/dbspace/.mida.db-journal"
aul_files += "${prefix}/bin/aul_mime.sh"
aul_files += "${prefix}/bin/aul_test"
aul_files += "${prefix}/bin/app_launcher"
aul_files += "${prefix}/bin/amd_session_agent"
aul_files += "${prefix}/share/aul/miregex/*"
aul_files += "${prefix}/share/aul/service/*"
aul_files += "${prefix}/share/aul/preload_list.txt"
aul_files += "${prefix}/share/aul/preexec_list.txt"
aul_files += "${systemd_unitdir}/system/ac.service"
aul_files += "${prefix}/lib/systemd/user/amd_session_agent.service"
aul_files += "${prefix}/bin/amd"
aul_files += "${prefix}/bin/daemon-manager-release-agent"
aul_files += "${prefix}/bin/daemon-manager-launch-agent"
MANIFESTFILES_${PN} = "aul.manifest"

aul-dev_files = ""
aul-dev_files += "${prefix}/include/aul/*.h"
aul-dev_files += "${prefix}/lib/*.so"
aul-dev_files += "${prefix}/lib/pkgconfig/*.pc"

aul-test_files = ""
aul-test_files += "${prefix}/bin/launch_app"
aul-test_files += "${prefix}/bin/open_app"
aul-test_files += "${prefix}/bin/aul_service.sh"
aul-test_files += "${prefix}/bin/aul_service_test.sh"

FILES_${PN} = "${aul_files}"
FILES_${PN}-dev = "${aul-dev_files}"
FILES_${PN}-test = "${aul-test_files}"

PKG_aul= "aul"
PKG_aul-dev= "aul-dev"
PKG_aul-test= "aul-test"

require aul-extraconf.inc

