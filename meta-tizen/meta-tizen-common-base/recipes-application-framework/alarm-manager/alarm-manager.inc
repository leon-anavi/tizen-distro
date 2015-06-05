DESCRIPTION = "Alarm library"
HOMEPAGE = "http://nohomepage.org"
SECTION = "Application Framework/Libraries"
LICENSE = "Apache-2.0"
PV = "0.4.86"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by alarm-manager


#PROVIDES by libalarm
PROVIDES += "libalarm"


#PROVIDES by alarm-server
PROVIDES += "alarm-server"


#PROVIDES by libalarm-dev
PROVIDES += "libalarm-dev"


RDEPENDS = ""
#RDEPENDS of libalarm (libalarm)
RDEPENDS_libalarm += "alarm-server"

#RDEPENDS of alarm-server (alarm-server)
RDEPENDS_alarm-server += "systemd"

#RDEPENDS of libalarm-dev (libalarm-dev)
RDEPENDS_libalarm-dev += "libalarm"


DEPENDS = ""
#DEPENDS of alarm-manager
DEPENDS += "dlog"
DEPENDS += "dbus"
DEPENDS += "app-svc"
DEPENDS += "tizen-platform-config"
inherit pkgconfig
DEPENDS += "bundle"
DEPENDS += "aul"
DEPENDS += "system-server"
DEPENDS += "dbus-glib"
DEPENDS += "security-server"
DEPENDS += "heynoti"
DEPENDS += "glib-2.0"
DEPENDS += "libtapi"
DEPENDS += "vconf"
DEPENDS += "libslp-db-util"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/alarm-manager.manifest .
 
 
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
  
  dbus-binding-tool --mode=glib-server --prefix=alarm_manager ./alarm_mgr.xml > ./include/alarm-skeleton.h
  dbus-binding-tool --mode=glib-client --prefix=alarm_manager ./alarm_mgr.xml > ./include/alarm-stub.h
  dbus-binding-tool --mode=glib-server --prefix=alarm_client ./alarm-expire.xml > ./include/alarm-expire-skeleton.h
  dbus-binding-tool --mode=glib-client --prefix=alarm_client ./alarm-expire.xml > ./include/alarm-expire-stub.h
  
  autotools_do_configure
  oe_runmake ${PARALLEL_MAKE}
  
  
  
}
EXTRA_OECONF += " --disable-static"

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
 
 install -d ${D}${systemd_unitdir}/system/multi-user.target.wants
 install -m0644 ${S}/packaging/alarm-server.service ${D}${systemd_unitdir}/system
 ln -sf ../alarm-server.service ${D}${systemd_unitdir}/system/multi-user.target.wants/alarm-server.service
 
 mkdir -p ${D}/${sysconfdir}/udev/rules.d
 install -m0644  ${S}/packaging/60-alarm-manager-rtc.rules ${D}${sysconfdir}/udev/rules.d/
 
 mkdir -p ${D}/${sysconfdir}/dbus-1/system.d
 install -m0644  ${S}/packaging/alarm-service.conf ${D}${sysconfdir}/dbus-1/system.d/
 
 
}

pkg_postinst_alarm-server() {
    #!/bin/sh -e

    vconftool set -t int db/system/timechange 0
    vconftool set -t double db/system/timechange_external 0
    vconftool set -t int memory/system/timechanged 0 -i -g 5000
    systemctl daemon-reload
    if [ $1 == 1 ]; then
        systemctl restart alarm-server.service
    fi

}

pkg_postinst_libalarm() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_prerm_alarm-server() {
    #!/bin/sh -e

    if [ $1 == 0 ]; then
        systemctl stop alarm-server.service
    fi

}

pkg_postrm_libalarm() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_alarm-server() {
    #!/bin/sh -e

    systemctl daemon-reload
    if [ "$1" == 1 ]; then
        systemctl restart net-config.service
    fi

}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " libalarm "
PACKAGES += " alarm-server "
PACKAGES += " libalarm-dev "

libalarm_files = ""
libalarm_files += "${prefix}/lib/libalarm.so.0.0.0"
libalarm_files += "${prefix}/lib/libalarm.so.0"
MANIFESTFILES_libalarm = "alarm-manager.manifest"

alarm-server_files = ""
alarm-server_files += "${prefix}/bin/alarm-server"
alarm-server_files += "${systemd_unitdir}/system/multi-user.target.wants/alarm-server.service"
alarm-server_files += "${systemd_unitdir}/system/alarm-server.service"
alarm-server_files += "${sysconfdir}/dbus-1/system.d/alarm-service.conf"
alarm-server_files += "%config ${sysconfdir}/udev/rules.d/60-alarm-manager-rtc.rules"
CONFFILES_alarm-server = ""
CONFFILES_alarm-server += "${sysconfdir}/dbus-1/system.d/alarm-service.conf"
MANIFESTFILES_alarm-server = "alarm-manager.manifest"

libalarm-dev_files = ""
libalarm-dev_files += "${prefix}/include/*.h"
libalarm-dev_files += "${prefix}/lib/pkgconfig/*.pc"
libalarm-dev_files += "${prefix}/lib/libalarm.so"
MANIFESTFILES_libalarm-dev = "alarm-manager.manifest"

FILES_libalarm = "${libalarm_files}"
FILES_alarm-server = "${alarm-server_files}"
FILES_libalarm-dev = "${libalarm-dev_files}"

PKG_libalarm= "libalarm"
PKG_alarm-server= "alarm-server"
PKG_libalarm-dev= "libalarm-dev"

require alarm-manager-extraconf.inc

