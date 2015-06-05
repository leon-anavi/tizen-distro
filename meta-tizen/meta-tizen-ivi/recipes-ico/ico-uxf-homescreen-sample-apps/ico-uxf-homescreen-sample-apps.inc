DESCRIPTION = "HomeScreen sample application"
HOMEPAGE = "http://nohomepage.org"
SECTION = "Automotive/ICO Homescreen"
LICENSE = "Apache-2.0"
PV = "0.9.8"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by ico-uxf-homescreen-sample-apps


RDEPENDS = ""
#RDEPENDS of ico-uxf-homescreen-sample-apps (${PN})
RDEPENDS_${PN} += "genivi-shell"
RDEPENDS_${PN} += "ico-uxf-utilities"
RDEPENDS_${PN} += "edbus"
RDEPENDS_${PN} += "ico-uxf-homescreen"
RDEPENDS_${PN} += "evas"
RDEPENDS_${PN} += "dbus"
RDEPENDS_${PN} += "capi-appfw-application"
RDEPENDS_${PN} += "weston-ivi-shell"
RDEPENDS_${PN} += "weston"
RDEPENDS_${PN} += "ico-vic-amb-plugin"
RDEPENDS_${PN} += "automotive-message-broker"
RDEPENDS_${PN} += "elementary"
RDEPENDS_${PN} += "ecore"
RDEPENDS_${PN} += "weekeyboard"
RDEPENDS_${PN} += "ico-uxf-weston-plugin"


DEPENDS = ""
#DEPENDS of ico-uxf-homescreen-sample-apps
DEPENDS += "edje"
DEPENDS += "ico-uxf-utilities"
DEPENDS += "edbus"
DEPENDS += "evas"
DEPENDS += "tizen-platform-config"
DEPENDS += "pulseaudio"
DEPENDS += "capi-appfw-application"
inherit pkgconfig
DEPENDS += "bundle"
DEPENDS += "glib-2.0"
DEPENDS += "eina"
DEPENDS += "aul"
DEPENDS += "elementary"
DEPENDS += "ecore"
DEPENDS += "dbus"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q -n ico-uxf-homescreen-sample-apps-0.9.8
 cp ${S}/packaging/ico-uxf-homescreen-sample-apps.manifest .
 
 
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
 
 # create tizen package metadata related directories
 mkdir -p ${D}${prefix}/share/packages/
 mkdir -p ${D}${prefix}/share/icons/default/small
 
 mkdir -p ${D}${prefix}/apps/org.tizen.ico.app-soundsample/bin/
 mkdir -p ${D}${prefix}/apps/org.tizen.ico.app-soundsample/sounds/
 mkdir -p ${D}${prefix}/apps/org.tizen.ico.app-soundsample/res/images/
 install -m 0644 ico-app-soundsample/soundsample_config.txt ${D}${prefix}/apps/org.tizen.ico.app-soundsample/res/
 install -m 0644 ico-app-soundsample/sound_bg.png ${D}${prefix}/apps/org.tizen.ico.app-soundsample/res/images/
 install -m 0644 ico-app-soundsample/org.tizen.ico.app-soundsample.png ${D}${prefix}/share/icons/default/small/
 install -m 0644 ico-app-soundsample/musicbox.wav ${D}${prefix}/apps/org.tizen.ico.app-soundsample/sounds/
 install -m 0644 ico-app-soundsample/org.tizen.ico.app-soundsample.xml ${D}${prefix}/share/packages/
 
 mkdir -p ${D}${prefix}/apps/org.tizen.ico.app-vicsample/bin/
 mkdir -p ${D}${prefix}/apps/org.tizen.ico.app-vicsample/res/images/
 install -m 0644 ico-app-vicsample/vicsample_config.txt ${D}${prefix}/apps/org.tizen.ico.app-vicsample/res/
 install -m 0644 ico-app-vicsample/vicinfo_bg.png ${D}${prefix}/apps/org.tizen.ico.app-vicsample/res/images/
 install -m 0644 ico-app-vicsample/org.tizen.ico.app-vicsample.png ${D}${prefix}/share/icons/default/small/
 install -m 0644 ico-app-vicsample/org.tizen.ico.app-vicsample.xml ${D}${prefix}/share/packages/
 
 # configurations(ico-app-miscellaneous)
 # install tizen package metadata for weston-terminal
 install -m 0644 ico-app-miscellaneous/terminal.xml ${D}${prefix}/share/packages/
 
 # install tizen package metadata for weekeyboard
 install -m 0644 ico-app-miscellaneous/weekeyboard.xml ${D}${prefix}/share/packages/
 
 # install tizen package metadata for mock navigator
 install -m 0644 ico-app-miscellaneous/navigator.xml ${D}${prefix}/share/packages/
 install -m 0644 ico-app-miscellaneous/navigator.png ${D}${prefix}/share/icons/default/small/
 
 
}

pkg_postinst_${PN}() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
    # This icons exists in main weston package so we don't package it in.
    # Create a symbolic link to it instead.
    ln -sf $D${prefix}/share/weston/terminal.png $D${prefix}/share/icons/default/small/
    # Update the app database.
    pkg_initdb
    ail_initdb

}

pkg_postrm_${PN}() {
    #!/bin/sh -e

    if [ "$1" = "0" ]; then
    [ "x$D" == "x" ] && ldconfig
    rm -f $D${prefix}/share/applications/org.tizen.ico.app-soundsample.desktop
    rm -f $D${prefix}/share/applications/org.tizen.ico.app-vicsample.desktop
    rm -f $D${prefix}/share/applications/terminal.desktop
    rm -f $D${prefix}/share/icons/default/small/terminal.png
    # Update the app database.
    pkg_initdb
    ail_initdb
    fi

}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " ico-uxf-homescreen-sample-apps "

ico-uxf-homescreen-sample-apps_files = ""
ico-uxf-homescreen-sample-apps_files += "${prefix}/apps/org.tizen.ico.app-soundsample/bin/ico-app-soundsample"
ico-uxf-homescreen-sample-apps_files += "${prefix}/apps/org.tizen.ico.app-soundsample/res/soundsample_config.txt"
ico-uxf-homescreen-sample-apps_files += "${prefix}/apps/org.tizen.ico.app-soundsample/res/images/sound_bg.png"
ico-uxf-homescreen-sample-apps_files += "${prefix}/apps/org.tizen.ico.app-soundsample/sounds/musicbox.wav"
ico-uxf-homescreen-sample-apps_files += "${prefix}/share/icons/default/small/org.tizen.ico.app-soundsample.png"
ico-uxf-homescreen-sample-apps_files += "${prefix}/share/packages/org.tizen.ico.app-soundsample.xml"
ico-uxf-homescreen-sample-apps_files += "${prefix}/apps/org.tizen.ico.app-vicsample/bin/ico-app-vicsample"
ico-uxf-homescreen-sample-apps_files += "${prefix}/apps/org.tizen.ico.app-vicsample/res/vicsample_config.txt"
ico-uxf-homescreen-sample-apps_files += "${prefix}/apps/org.tizen.ico.app-vicsample/res/images/vicinfo_bg.png"
ico-uxf-homescreen-sample-apps_files += "${prefix}/share/icons/default/small/org.tizen.ico.app-vicsample.png"
ico-uxf-homescreen-sample-apps_files += "${prefix}/share/packages/org.tizen.ico.app-vicsample.xml"
ico-uxf-homescreen-sample-apps_files += "${prefix}/share/packages/terminal.xml"
ico-uxf-homescreen-sample-apps_files += "${prefix}/share/packages/navigator.xml"
ico-uxf-homescreen-sample-apps_files += "${prefix}/share/packages/weekeyboard.xml"
ico-uxf-homescreen-sample-apps_files += "${prefix}/share/icons/default/small/navigator.png"
MANIFESTFILES_${PN} = "ico-uxf-homescreen-sample-apps.manifest"

FILES_${PN} = "${ico-uxf-homescreen-sample-apps_files}"

PKG_ico-uxf-homescreen-sample-apps= "ico-uxf-homescreen-sample-apps"

require ico-uxf-homescreen-sample-apps-extraconf.inc

