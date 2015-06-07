DESCRIPTION = "Messaging Framework Library"
HOMEPAGE = "http://nohomepage.org"
SECTION = "System/Libraries"
LICENSE = "Apache-2.0"
PV = "0.9.4"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by mms-plugin
PROVIDES += "mms-plugin"


#PROVIDES by msg-service-tools
PROVIDES += "msg-service-tools"


#PROVIDES by sms-plugin
PROVIDES += "sms-plugin"


#PROVIDES by msg-service-dev
PROVIDES += "msg-service-dev"


#PROVIDES by msg-service


RDEPENDS = ""
#RDEPENDS of mms-plugin (mms-plugin)
RDEPENDS_mms-plugin += "glibc"
RDEPENDS_mms-plugin += "msg-service"

#RDEPENDS of msg-service-tools (${PN}-tools)
RDEPENDS_${PN}-tools += "sqlite3"
RDEPENDS_${PN}-tools += "glibc"
RDEPENDS_${PN}-tools += "vconf"
RDEPENDS_${PN}-tools += "msg-service"

#RDEPENDS of sms-plugin (sms-plugin)
RDEPENDS_sms-plugin += "glibc"
RDEPENDS_sms-plugin += "msg-service"

#RDEPENDS of msg-service-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "msg-service"

#RDEPENDS of msg-service (${PN})
RDEPENDS_${PN} += "sqlite3"
RDEPENDS_${PN} += "glibc"
RDEPENDS_${PN} += "systemd"
RDEPENDS_${PN} += "vconf"


DEPENDS = ""
#DEPENDS of msg-service
DEPENDS += "libxml2"
DEPENDS += "capi-appfw-application"
DEPENDS += "aul"
DEPENDS += "contacts-service"
DEPENDS += "curl"
DEPENDS += "libmm-session"
DEPENDS += "system-server"
DEPENDS += "systemd"
inherit tizen_cmake
DEPENDS += "drm-client"
DEPENDS += "notification"
DEPENDS += "app-svc"
inherit pkgconfig
DEPENDS += "dlog"
DEPENDS += "glib-2.0"
DEPENDS += "libmm-fileinfo"
DEPENDS += "alarm-manager"
DEPENDS += "sensor"
DEPENDS += "libwbxml2"
DEPENDS += "libsvi"
DEPENDS += "tizen-platform-config"
DEPENDS += "libmedia-thumbnail"
DEPENDS += "libtapi"
DEPENDS += "security-server"
DEPENDS += "vconf"
DEPENDS += "libslp-db-util"
DEPENDS += "libnet-client"
DEPENDS += "libmm-sound"
DEPENDS += "libmm-utility"
DEPENDS += "libmm-player"
DEPENDS += "capi-network-connection"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/msg-service.manifest ${S}/packaging/msg-service-devel.manifest ${S}/packaging/msg-service-tools.manifest ${S}/packaging/sms-plugin.manifest ${S}/packaging/mms-plugin.manifest .
 
 
 
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
 	-DTZ_SYS_SHARE=${prefix}/share \
 	-DUNITDIR_USER=${prefix}/lib/systemd/user \
 	-DTZ_SYS_SMACK=${sysconfdir}/smack
 
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
 mkdir -p ${D}/etc/config
 
 mkdir -p ${D}/var/log/msgfw
 
 
   oe_runmake \
         DESTDIR=${D} \
         INSTALL_ROOT=${D} \
         BINDIR=${prefix}/bin \
   install  
   rm -f ${D}${infodir}/dir 
   find ${D} -regex ".*\.la$" | xargs rm -f -- 
   find ${D} -regex ".*\.a$" | xargs rm -f --
 
 mkdir -p ${D}${prefix}/lib/systemd/user/tizen-middleware.target.wants
 #install -m 0644 ${S}/packaging/msg-service.service ${D}${prefix}/lib/systemd/user/
 ln -s ../msg-service.service ${D}${prefix}/lib/systemd/user/tizen-middleware.target.wants/msg-service.service
 ln -s ../msg-service-log.service ${D}${prefix}/lib/systemd/user/tizen-middleware.target.wants/msg-service-log.service
 
 mkdir -p  ${D}${sysconfdir}/rc.d/rc3.d
 ln -s ${sysconfdir}/rc.d/init.d/msg-server  ${D}${sysconfdir}/rc.d/rc3.d/S70msg-server
 mkdir -p  ${D}${sysconfdir}/rc.d/rc5.d
 ln -s ${sysconfdir}/rc.d/init.d/msg-server  ${D}${sysconfdir}/rc.d/rc5.d/S70msg-server
 
 rm ${D}/etc/config/sysinfo-message.emul.xml
 
 
 
}

pkg_postinst_mms-plugin() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postinst_${PN}() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
    /bin/systemctl daemon-reload
    if [ "$1" = "1" ]; then
        systemctl stop msg-service.service
    fi

}

pkg_postinst_${PN}() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postinst_sms-plugin() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_mms-plugin() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_${PN}() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_sms-plugin() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_${PN}() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " mms-plugin "
PACKAGES += " msg-service-tools "
PACKAGES += " sms-plugin "
PACKAGES += " msg-service-dev "
PACKAGES += " msg-service "

mms-plugin_files = ""
mms-plugin_files += "${prefix}/lib/libmsg_mms_plugin.so"
MANIFESTFILES_mms-plugin = "mms-plugin.manifest"

msg-service-tools_files = ""
msg-service-tools_files += "${prefix}/bin/msg-helper"
msg-service-tools_files += "${prefix}/bin/msg-server"
msg-service-tools_files += "${prefix}/share/media/Sherbet.wav"
msg-service-tools_files += "${prefix}/share/msg-service/plugin.cfg"
msg-service-tools_files += "${sysconfdir}/rc.d/init.d/msg-server"
msg-service-tools_files += "${sysconfdir}/rc.d/rc3.d/S70msg-server"
msg-service-tools_files += "${sysconfdir}/rc.d/rc5.d/S70msg-server"
msg-service-tools_files += "${prefix}/lib/systemd/user/msg-service.service"
msg-service-tools_files += "${prefix}/lib/systemd/user/msg-service-log.service"
msg-service-tools_files += "${prefix}/lib/systemd/user/tizen-middleware.target.wants/msg-service.service"
msg-service-tools_files += "${prefix}/lib/systemd/user/tizen-middleware.target.wants/msg-service-log.service"
msg-service-tools_files += "${sysconfdir}/config/sysinfo-message.xml"
msg-service-tools_files += "/var/log/msgfw"
MANIFESTFILES_${PN}-tools = "msg-service-tools.manifest"

sms-plugin_files = ""
sms-plugin_files += "${prefix}/lib/libmsg_sms_plugin.so"
MANIFESTFILES_sms-plugin = "sms-plugin.manifest"

msg-service-dev_files = ""
msg-service-dev_files += "${prefix}/lib/libmsg_mapi.so"
msg-service-dev_files += "${prefix}/lib/pkgconfig/msg-service.pc"
msg-service-dev_files += "${prefix}/include/msg-service/*"
MANIFESTFILES_${PN}-dev = "msg-service-devel.manifest"

msg-service_files = ""
msg-service_files += "${prefix}/lib/libmsg_plugin_manager.so"
msg-service_files += "${prefix}/lib/libmsg_mapi.so.*"
msg-service_files += "${prefix}/lib/libmsg_framework_handler.so"
msg-service_files += "${prefix}/lib/libmsg_transaction_manager.so"
msg-service_files += "${prefix}/lib/libmsg_utils.so"
msg-service_files += "${prefix}/lib/libmsg_transaction_proxy.so"
msg-service_files += "${prefix}/lib/libmsg_vobject.so"
msg-service_files += "${prefix}/share/msg-service/msg_service-init-DB.sh"
MANIFESTFILES_${PN} = "msg-service.manifest"

FILES_mms-plugin = "${mms-plugin_files}"
FILES_${PN}-tools = "${msg-service-tools_files}"
FILES_sms-plugin = "${sms-plugin_files}"
FILES_${PN}-dev = "${msg-service-dev_files}"
FILES_${PN} = "${msg-service_files}"

PKG_mms-plugin= "mms-plugin"
PKG_msg-service-tools= "msg-service-tools"
PKG_sms-plugin= "sms-plugin"
PKG_msg-service-dev= "msg-service-dev"
PKG_msg-service= "msg-service"

require msg-service-extraconf.inc

