DESCRIPTION = "Download the contents in background"
HOMEPAGE = "http://nohomepage.org"
SECTION = "System/Libraries"
LICENSE = "Apache-2.0"
PV = "1.1.6"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by download-provider


#PROVIDES by download-provider-dev
PROVIDES += "download-provider-dev"


RDEPENDS = ""
#RDEPENDS of download-provider (${PN})
RDEPENDS_${PN} += "sqlite3"
RDEPENDS_${PN} += "connman"
RDEPENDS_${PN} += "glibc"
RDEPENDS_${PN} += "vconf"
RDEPENDS_${PN} += "net-config"

#RDEPENDS of download-provider-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "download-provider"


DEPENDS = ""
#DEPENDS of download-provider
DEPENDS += "dlog"
DEPENDS += "xdgmime"
DEPENDS += "systemd"
inherit tizen_cmake
DEPENDS += "notification"
DEPENDS += "app-svc"
inherit pkgconfig
#Replace "DEPENDS" on gettext by "inherit gettext"
inherit gettext
DEPENDS += "glib-2.0"
DEPENDS += "libsoup-2.4"
DEPENDS += "sqlite3"
DEPENDS += "libprivilege-control"
DEPENDS += "capi-appfw-app-manager"
DEPENDS += "tizen-platform-config"
DEPENDS += "bundle"
DEPENDS += "smack"
DEPENDS += "vconf"
DEPENDS += "libwifi-direct"
DEPENDS += "capi-network-connection"
DEPENDS_append_class-native = " fdupes-native"
DEPENDS_append_class-target = " fdupes-native"
DEPENDS += "capi-base-common"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 
 
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
 
 
 CFLAGS="${CFLAGS:-$CFLAGS} -fPIC -D_REENTRANT -fvisibility=hidden"; export CFLAGS
 FFLAGS="${FFLAGS:-$CFLAGS} -fPIC -fvisibility=hidden"; export FFLAGS
 LDFLAGS="${LDFLAGS} -Wl,--as-needed -Wl,--hash-style=both"; export LDFLAGS
 
 
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
          -DBIN_INSTALL_DIR:PATH=${prefix}/bin \
          -DPKG_NAME=download-provider \
          -DPKG_VERSION=1.1.6 \
          -DPKG_RELEASE=0 \
          -DIMAGE_DIR:PATH=${prefix}/share/download-provider/images \
          -DLOCALE_DIR:PATH=${prefix}/share/locale \
          -DSYSTEMD_DIR:PATH=${systemd_unitdir}/system \
          -DDATABASE_SCHEMA_DIR=${prefix}/share/download-provider/sql \
          -DDATABASE_SCHEMA_FILE=${prefix}/share/download-provider/sql/download-provider-schema.sql \
          -DSUPPORT_WIFI_DIRECT:BOOL=OFF \
          -DSUPPORT_LOG_MESSAGE:BOOL=ON \
          -DSUPPORT_CHECK_IPC:BOOL=ON
 
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
 mkdir -p ${D}${prefix}/share/download-provider
 mkdir -p ${D}${systemd_unitdir}/system/default.target.wants
 mkdir -p ${D}${systemd_unitdir}/system/sockets.target.wants
 ln -s ../download-provider.service ${D}${systemd_unitdir}/system/default.target.wants/
 ln -s ../download-provider.socket ${D}${systemd_unitdir}/system/sockets.target.wants/
 
 #find_lang download-provider
 
 #fdupes ${D}${prefix}/share/locale
 
 
}

pkg_postinst_${PN}() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
    if [ $1 -eq 1 ] ; then 
            # Initial installation 
            /usr/bin/systemctl preset download-provider.service >/dev/null 2>&1 || : 
    fi 
    vconftool set -t int db/setting/default_memory/wap 0

}

pkg_prerm_${PN}() {
    #!/bin/sh -e

    if [ $1 -eq 0 ] ; then 
            # Package removal, not upgrade 
            /usr/bin/systemctl --no-reload disable download-provider.service > /dev/null 2>&1 || : 
            /usr/bin/systemctl stop download-provider.service > /dev/null 2>&1 || : 
    fi 

}

pkg_postrm_${PN}() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
    /usr/bin/systemctl daemon-reload >/dev/null 2>&1 || : 

}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " download-provider "
PACKAGES += " download-provider-dev "

download-provider_files = ""
download-provider_files += "${prefix}/bin/download-provider"
download-provider_files += "${prefix}/share/download-provider/images/*.png"
download-provider_files += "${prefix}/share/download-provider/images/*.gif"
download-provider_files += "${prefix}/lib/libdownloadagent2.so*"
download-provider_files += "${prefix}/lib/libdownload-provider-interface.so*"
download-provider_files += "${systemd_unitdir}/system/download-provider.service"
download-provider_files += "${systemd_unitdir}/system/default.target.wants/download-provider.service"
download-provider_files += "${systemd_unitdir}/system/download-provider.socket"
download-provider_files += "${systemd_unitdir}/system/sockets.target.wants/download-provider.socket"
download-provider_files += "${prefix}/share/download-provider/sql/download-provider-schema.sql"
MANIFESTFILES_${PN} = "download-provider.manifest"

download-provider-dev_files = ""
download-provider-dev_files += "${prefix}/lib/libdownloadagent2.so"
download-provider-dev_files += "${prefix}/lib/libdownload-provider-interface.so"
download-provider-dev_files += "${prefix}/include/download-provider/download-provider-defs.h"
download-provider-dev_files += "${prefix}/include/download-provider/download-provider-interface.h"
download-provider-dev_files += "${prefix}/lib/pkgconfig/download-provider.pc"
download-provider-dev_files += "${prefix}/lib/pkgconfig/download-provider-interface.pc"
MANIFESTFILES_${PN}-dev = "download-provider.manifest"

FILES_${PN} = "${download-provider_files}"
FILES_${PN}-dev = "${download-provider-dev_files}"

PKG_download-provider= "download-provider"
PKG_download-provider-dev= "download-provider-dev"

require download-provider-extraconf.inc

