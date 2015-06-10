DESCRIPTION = "Sync agent FW Library"
HOMEPAGE = "http://nohomepage.org"
SECTION = "System/Service"
LICENSE = "Apache-2.0"
PV = "0.1.91"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by sync-agent-dev
PROVIDES += "sync-agent-dev"


#PROVIDES by common-public-plugins
PROVIDES += "common-public-plugins"


#PROVIDES by sync-agent


RDEPENDS = ""
#RDEPENDS of sync-agent-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "sync-agent"

#RDEPENDS of sync-agent (${PN})
RDEPENDS_${PN} += "glibc"


DEPENDS = ""
#DEPENDS of sync-agent
DEPENDS += "libslp-location"
DEPENDS += "libxml2"
DEPENDS += "aul"
DEPENDS += "contacts-service"
DEPENDS += "libgcrypt"
DEPENDS += "capi-base-common"
DEPENDS += "curl"
DEPENDS += "dbus-glib"
DEPENDS += "libsoup-2.4"
inherit tizen_cmake
DEPENDS += "app-svc"
inherit pkgconfig
DEPENDS += "dlog"
DEPENDS += "glib-2.0"
DEPENDS += "system-server"
DEPENDS += "msg-service"
DEPENDS += "alarm-manager"
DEPENDS += "libaccounts-svc"
DEPENDS += "libwbxml2"
DEPENDS += "tizen-platform-config"
DEPENDS += "bundle"
DEPENDS += "sqlite3"
DEPENDS += "libtapi"
DEPENDS += "util-linux"
DEPENDS += "vconf"
DEPENDS += "libslp-db-util"
DEPENDS += "capi-system-info"
DEPENDS += "libslp-memo"
DEPENDS += "syspopup"
DEPENDS += "calendar-service"
DEPENDS += "capi-network-connection"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/sync-agent.manifest ${S}/packaging/sync-agent-devel.manifest ${S}/packaging/common-public-plugins.manifest .
 
 
 
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
PACKAGES += " sync-agent-dev "
PACKAGES += " common-public-plugins "
PACKAGES += " sync-agent "

sync-agent-dev_files = ""
sync-agent-dev_files += "${prefix}/include/sync_agent.h"
sync-agent-dev_files += "${prefix}/include/sync-agent/*"
sync-agent-dev_files += "${prefix}/lib/pkgconfig/sync-agent.pc"
MANIFESTFILES_${PN}-dev = "sync-agent-devel.manifest"

common-public-plugins_files = ""
common-public-plugins_files += "${prefix}/lib/sync-agent/common-public/*"
MANIFESTFILES_common-public-plugins = "common-public-plugins.manifest"

sync-agent_files = ""
sync-agent_files += "${prefix}/lib/*.so"
sync-agent_files += "${prefix}/lib/*.so.*"
MANIFESTFILES_${PN} = "sync-agent.manifest"

FILES_${PN}-dev = "${sync-agent-dev_files}"
FILES_common-public-plugins = "${common-public-plugins_files}"
FILES_${PN} = "${sync-agent_files}"

PKG_sync-agent-dev= "sync-agent-dev"
PKG_common-public-plugins= "common-public-plugins"
PKG_sync-agent= "sync-agent"

require sync-agent-extraconf.inc

