DESCRIPTION = "Sample homescreen and system controller"
HOMEPAGE = "http://nohomepage.org"
SECTION = "Automotive/ICO Homescreen"
LICENSE = "Apache-2.0"
PV = "0.9.23"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by ico-uxf-homescreen-system-controller-dev
PROVIDES += "ico-uxf-homescreen-system-controller-dev"


#PROVIDES by ico-uxf-homescreen


RDEPENDS = ""
#RDEPENDS of ico-uxf-homescreen-system-controller-dev (${PN}-system-controller-dev)
RDEPENDS_${PN}-system-controller-dev += "edje"
RDEPENDS_${PN}-system-controller-dev += "ico-uxf-homescreen"
RDEPENDS_${PN}-system-controller-dev += "evas"
RDEPENDS_${PN}-system-controller-dev += "app-svc"
RDEPENDS_${PN}-system-controller-dev += "glib-2.0"
RDEPENDS_${PN}-system-controller-dev += "eina"
RDEPENDS_${PN}-system-controller-dev += "capi-base-common-dev"
RDEPENDS_${PN}-system-controller-dev += "ecore"

#RDEPENDS of ico-uxf-homescreen (${PN})
RDEPENDS_${PN} += "genivi-shell"
RDEPENDS_${PN} += "ico-uxf-utilities"
RDEPENDS_${PN} += "pkgmgr"
RDEPENDS_${PN} += "weston-ivi-shell"
RDEPENDS_${PN} += "weston"
RDEPENDS_${PN} += "ail"
RDEPENDS_${PN} += "system-controller"
RDEPENDS_${PN} += "ico-uxf-weston-plugin"


DEPENDS = ""
#DEPENDS of ico-uxf-homescreen
DEPENDS += "edje"
DEPENDS += "genivi-shell"
DEPENDS += "pkgmgr"
DEPENDS += "capi-appfw-application"
DEPENDS += "aul"
DEPENDS += "eina"
DEPENDS += "json-glib"
DEPENDS += "notification"
DEPENDS += "app-svc"
inherit pkgconfig
DEPENDS += "glib-2.0"
DEPENDS += "wayland"
DEPENDS += "virtual/libgl"
DEPENDS += "boost"
DEPENDS += "ico-uxf-weston-plugin"
DEPENDS += "ico-uxf-utilities"
DEPENDS += "evas"
DEPENDS += "tizen-platform-config"
DEPENDS += "murphy"
DEPENDS += "bundle"
DEPENDS += "weston-ivi-shell"
DEPENDS += "libwebsockets"
DEPENDS += "ecore"
DEPENDS += "virtual/egl"
DEPENDS += "dbus"
DEPENDS += "ail"
DEPENDS_append_class-native = " fdupes-native"
DEPENDS_append_class-target = " fdupes-native"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q -n ico-uxf-homescreen-0.9.23
 cp ${S}/packaging/ico-uxf-homescreen.manifest .
 
 mkdir -p weston
 cp -av ${prefix}/share/genivi-shell/protocol/*.xml weston/
 
 ls weston/*.xml | while read protocol ; do
 
     ${prefix}/bin/wayland-scanner client-header \
         < "${protocol}" > "${protocol/.xml/}-client-protocol.h"
 
     ${prefix}/bin/wayland-scanner code \
         < "${protocol}" > "${protocol/.xml/.c}"
 
 done
 
 
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
  
  
   
  autotools_do_configure
  oe_runmake ${PARALLEL_MAKE}
  
  
  
}
EXTRA_OECONF += ""

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
 
 cp tool/ico_clear_screen ${D}${prefix}/bin
 cp tool/ico_change_loginuser ${D}${prefix}/bin
 cp tool/notification/ico_del_notification ${D}${prefix}/bin
 cp tool/notification/ico_dump_notification ${D}${prefix}/bin
 cp tool/notification/ico_send_notification ${D}${prefix}/bin
 cp tool/notification/ico_send_notification2 ${D}${prefix}/bin
 
 #fdupes ${D}
 
 
}

pkg_postinst_${PN}() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
    # Update the app database.
    pkg_initdb
    ail_initdb

}

pkg_postrm_${PN}() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
    rm -f $D${prefix}/share/applications/org.tizen.ico.homescreen.desktop
    rm -f $D${prefix}/share/applications/org.tizen.ico.statusbar.desktop
    rm -f $D${prefix}/share/applications/org.tizen.ico.onscreen.desktop
    pkg_initdb
    ail_initdb

}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " ico-uxf-homescreen-system-controller-dev "
PACKAGES += " ico-uxf-homescreen "

ico-uxf-homescreen-system-controller-dev_files = ""
ico-uxf-homescreen-system-controller-dev_files += "${prefix}/include/ico-appfw/ico_syc_application.h"
ico-uxf-homescreen-system-controller-dev_files += "${prefix}/include/ico-appfw/ico_syc_appresctl.h"
ico-uxf-homescreen-system-controller-dev_files += "${prefix}/include/ico-appfw/ico_syc_common.h"
ico-uxf-homescreen-system-controller-dev_files += "${prefix}/include/ico-appfw/ico_syc_error.h"
ico-uxf-homescreen-system-controller-dev_files += "${prefix}/include/ico-appfw/ico_syc_inputctl.h"
ico-uxf-homescreen-system-controller-dev_files += "${prefix}/include/ico-appfw/ico_syc_msg.h"
ico-uxf-homescreen-system-controller-dev_files += "${prefix}/include/ico-appfw/ico_syc_msg_cmd_def.h"
ico-uxf-homescreen-system-controller-dev_files += "${prefix}/include/ico-appfw/ico_syc_private.h"
ico-uxf-homescreen-system-controller-dev_files += "${prefix}/include/ico-appfw/ico_syc_privilege.h"
ico-uxf-homescreen-system-controller-dev_files += "${prefix}/include/ico-appfw/ico_syc_public.h"
ico-uxf-homescreen-system-controller-dev_files += "${prefix}/include/ico-appfw/ico_syc_sysdef.h"
ico-uxf-homescreen-system-controller-dev_files += "${prefix}/include/ico-appfw/ico_syc_type.h"
ico-uxf-homescreen-system-controller-dev_files += "${prefix}/include/ico-appfw/ico_syc_userctl.h"
ico-uxf-homescreen-system-controller-dev_files += "${prefix}/include/ico-appfw/ico_syc_winctl.h"
MANIFESTFILES_${PN}-system-controller-dev = "ico-uxf-homescreen.manifest"

ico-uxf-homescreen_files = ""
ico-uxf-homescreen_files += "${prefix}/apps/org.tizen.ico.homescreen"
ico-uxf-homescreen_files += "${prefix}/apps/org.tizen.ico.statusbar"
ico-uxf-homescreen_files += "${prefix}/apps/org.tizen.ico.onscreen"
ico-uxf-homescreen_files += "${prefix}/share/packages/org.tizen.ico.homescreen.xml"
ico-uxf-homescreen_files += "${prefix}/share/packages/org.tizen.ico.statusbar.xml"
ico-uxf-homescreen_files += "${prefix}/share/packages/org.tizen.ico.onscreen.xml"
ico-uxf-homescreen_files += "${prefix}/lib/libico-appfw.*"
ico-uxf-homescreen_files += "${prefix}/bin/ico_clear_screen"
ico-uxf-homescreen_files += "${prefix}/bin/ico_change_loginuser"
ico-uxf-homescreen_files += "${prefix}/bin/ico_del_notification"
ico-uxf-homescreen_files += "${prefix}/bin/ico_dump_notification"
ico-uxf-homescreen_files += "${prefix}/bin/ico_send_notification"
ico-uxf-homescreen_files += "${prefix}/bin/ico_send_notification2"
ico-uxf-homescreen_files += "${prefix}/share/icons/default/small/org.tizen.ico.homescreen.png"
ico-uxf-homescreen_files += "${prefix}/share/icons/default/small/org.tizen.ico.statusbar.png"
ico-uxf-homescreen_files += "${prefix}/share/icons/default/small/org.tizen.ico.onscreen.png"
ico-uxf-homescreen_files += "${prefix}/apps/org.tizen.ico.system-controller/res/config"
MANIFESTFILES_${PN} = "ico-uxf-homescreen.manifest"

FILES_${PN}-system-controller-dev = "${ico-uxf-homescreen-system-controller-dev_files}"
FILES_${PN} = "${ico-uxf-homescreen_files}"

PKG_ico-uxf-homescreen-system-controller-dev= "ico-uxf-homescreen-system-controller-dev"
PKG_ico-uxf-homescreen= "ico-uxf-homescreen"

require ico-uxf-homescreen-extraconf.inc

