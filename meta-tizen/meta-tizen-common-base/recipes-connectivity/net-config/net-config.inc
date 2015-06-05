DESCRIPTION = "TIZEN Network Configuration Module"
HOMEPAGE = "http://nohomepage.org"
SECTION = "System/Network"
LICENSE = "Apache-2.0"
PV = "0.1.90_29"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by net-config


RDEPENDS = ""
#RDEPENDS of net-config (${PN})
RDEPENDS_${PN} += "systemd"
RDEPENDS_${PN} += "vconf"


DEPENDS = ""
#DEPENDS of net-config
DEPENDS += "libwifi-direct"
inherit tizen_cmake
DEPENDS += "syspopup"
inherit pkgconfig
DEPENDS += "dlog"
DEPENDS += "glib-2.0"
DEPENDS += "systemd"
DEPENDS += "libtapi"
DEPENDS += "vconf"
DEPENDS += "dbus-glib"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/net-config.manifest .
 
 
 
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
         ${EXTRA_OECMAKE} . -DCMAKE_INSTALL_PREFIX=${prefix}
 
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
 
 mkdir -p ${D}${prefix}/share/dbus-1/system-services
 cp resources/usr/share/dbus-1/services/net.netconfig.service ${D}${prefix}/share/dbus-1/system-services/net.netconfig.service
 mkdir -p ${D}${sysconfdir}/dbus-1/system.d
 cp resources/etc/dbus-1/system.d/net-config.conf ${D}${sysconfdir}/dbus-1/system.d/net-config.conf
 
 # Systemd service file
 mkdir -p ${D}${systemd_unitdir}/system
 cp resources/usr/lib/systemd/system/net-config.service ${D}${systemd_unitdir}/system/net-config.service
 mkdir -p ${D}${systemd_unitdir}/system/multi-user.target.wants/
 ln -s ../net-config.service ${D}${systemd_unitdir}/system/multi-user.target.wants/net-config.service
 
 #License
 mkdir -p ${D}${prefix}/share/license
 cp LICENSE.APLv2 ${D}${prefix}/share/license/net-config
 
 
}

pkg_postinst_${PN}() {
    #!/bin/sh -e

    vconftool set -t int memory/dnet/state 0 -i
    vconftool set -t int memory/wifi/state 0 -i
    vconftool set -t int memory/wifi/transfer_state 0 -i
    vconftool set -t int memory/wifi/strength 0 -i
    vconftool set -t int memory/wifi/bgscan_mode 0 -i
    vconftool set -t int memory/dnet/wifi 0 -i
    vconftool set -t int memory/dnet/network_config 0 -i
    vconftool set -t int memory/dnet/status 0 -i
    vconftool set -t string memory/dnet/ip "" -i
    vconftool set -t string memory/dnet/proxy "" -i
    vconftool set -t string memory/wifi/connected_ap_name "" -i
    vconftool set -t string db/wifi/bssid_address ""
    #Default Call Statistics
    vconftool set -t int db/dnet/statistics/cellular/totalsnt "0"
    vconftool set -t int db/dnet/statistics/cellular/totalrcv "0"
    vconftool set -t int db/dnet/statistics/cellular/lastsnt "0"
    vconftool set -t int db/dnet/statistics/cellular/lastrcv "0"
    vconftool set -t int db/dnet/statistics/wifi/totalsnt "0"
    vconftool set -t int db/dnet/statistics/wifi/totalrcv "0"
    vconftool set -t int db/dnet/statistics/wifi/lastsnt "0"
    vconftool set -t int db/dnet/statistics/wifi/lastrcv "0"
    vconftool set -t int file/private/wifi/last_power_state "0"
    systemctl daemon-reload
    if [ "$1" == "1" ]; then
        systemctl restart net-config.service
    fi

}

pkg_prerm_${PN}() {
    #!/bin/sh -e

    if [ "$1" == "0" ]; then
        systemctl stop net-config.service
    fi

}

pkg_postrm_${PN}() {
    #!/bin/sh -e

    systemctl daemon-reload
    if [ "$1" == "1" ]; then
        systemctl restart net-config.service
    fi

}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " net-config "

net-config_files = ""
net-config_files += "${prefix}/sbin/*"
net-config_files += "${prefix}/share/dbus-1/system-services/*"
net-config_files += "${sysconfdir}/dbus-1/system.d/*"
net-config_files += "${systemd_unitdir}/system/net-config.service"
net-config_files += "${systemd_unitdir}/system/multi-user.target.wants/net-config.service"
net-config_files += "${prefix}/share/license/net-config"
MANIFESTFILES_${PN} = "net-config.manifest"

FILES_${PN} = "${net-config_files}"

PKG_net-config= "net-config"

require net-config-extraconf.inc

