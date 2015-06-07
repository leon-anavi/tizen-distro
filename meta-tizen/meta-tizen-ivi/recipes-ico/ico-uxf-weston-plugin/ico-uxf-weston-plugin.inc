DESCRIPTION = "Weston Plugins for IVI"
HOMEPAGE = "http://nohomepage.org"
SECTION = "Automotive/ICO Homescreen"
LICENSE = "MIT"
PV = "0.9.23"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by ico-uxf-weston-plugin-dev
PROVIDES += "ico-uxf-weston-plugin-dev"


#PROVIDES by ico-uxf-weston-plugin


RDEPENDS = ""
#RDEPENDS of ico-uxf-weston-plugin-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "ico-uxf-weston-plugin"

#RDEPENDS of ico-uxf-weston-plugin (${PN})
RDEPENDS_${PN} += "weston"
RDEPENDS_${PN} += "genivi-shell"
RDEPENDS_${PN} += "weston-ivi-shell"
RDEPENDS_${PN} += "weekeyboard"


DEPENDS = ""
#DEPENDS of ico-uxf-weston-plugin
DEPENDS += "genivi-shell"
DEPENDS += "virtual/egl"
DEPENDS += "evas"
DEPENDS += "aul"
DEPENDS += "weston-ivi-shell"
inherit pkgconfig
DEPENDS += "weston"
DEPENDS += "virtual/libgl"
DEPENDS += "ecore"
DEPENDS += "pixman"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q -n ico-uxf-weston-plugin-0.9.23
 
 
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
 
 
   oe_runmake \
         DESTDIR=${D} \
         INSTALL_ROOT=${D} \
         BINDIR=${prefix}/bin \
   install  
   rm -f ${D}${infodir}/dir 
   find ${D} -regex ".*\.la$" | xargs rm -f -- 
   find ${D} -regex ".*\.a$" | xargs rm -f --
 
 # configurations
 mkdir -p ${D}${sysconfdir}/xdg/weston > /dev/null 2>&1
 mkdir -p ${D}${systemd_unitdir}/system/multi-user.target.wants > /dev/null 2>&1
 install -m 0644 settings/weston.ini ${D}${sysconfdir}/xdg/weston
 install -m 0644 settings/ico-pseudo-input-device.service ${D}${systemd_unitdir}/system/ico-pseudo-input-device.service
 ln -s ${systemd_unitdir}/system/ico-pseudo-input-device.service ${D}${systemd_unitdir}/system/multi-user.target.wants/ico-pseudo-input-device.service
 
 
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
PACKAGES += " ico-uxf-weston-plugin-dev "
PACKAGES += " ico-uxf-weston-plugin "

ico-uxf-weston-plugin-dev_files = ""
ico-uxf-weston-plugin-dev_files += "${prefix}/include/ico-uxf-weston-plugin/ico_input_mgr-client-protocol.h"
ico-uxf-weston-plugin-dev_files += "${prefix}/include/ico-uxf-weston-plugin/ico_window_mgr-client-protocol.h"
ico-uxf-weston-plugin-dev_files += "${prefix}/include/ico-uxf-weston-plugin/ico_input_mgr.h"
ico-uxf-weston-plugin-dev_files += "${prefix}/lib/libico-uxf-weston-plugin.so"
MANIFESTFILES_${PN}-dev = "ico-uxf-weston-plugin.manifest"

ico-uxf-weston-plugin_files = ""
ico-uxf-weston-plugin_files += "${prefix}/lib/weston/"
ico-uxf-weston-plugin_files += "${prefix}/lib/weston/*.so"
ico-uxf-weston-plugin_files += "${prefix}/lib/libico-uxf-weston-plugin.so.*"
ico-uxf-weston-plugin_files += "${prefix}/bin/ico_send_inputevent"
ico-uxf-weston-plugin_files += "${prefix}/bin/ico_pseudo_input_device"
ico-uxf-weston-plugin_files += "${systemd_unitdir}/system/ico-pseudo-input-device.service"
ico-uxf-weston-plugin_files += "${systemd_unitdir}/system/multi-user.target.wants/ico-pseudo-input-device.service"
ico-uxf-weston-plugin_files += "${sysconfdir}/xdg/weston/weston.ini"
CONFFILES_${PN} = ""
CONFFILES_${PN} += "${sysconfdir}/xdg/weston/weston.ini"
MANIFESTFILES_${PN} = "ico-uxf-weston-plugin.manifest"
DIRFILES_${PN} = ""
DIRFILES_${PN} += "${prefix}/lib/weston/"

FILES_${PN}-dev = "${ico-uxf-weston-plugin-dev_files}"
FILES_${PN} = "${ico-uxf-weston-plugin_files}"

PKG_ico-uxf-weston-plugin-dev= "ico-uxf-weston-plugin-dev"
PKG_ico-uxf-weston-plugin= "ico-uxf-weston-plugin"

require ico-uxf-weston-plugin-extraconf.inc

