DESCRIPTION = "Weston IVI Shell"
HOMEPAGE = "https://github.com/ntanibata/weston-ivi-shell/"
SECTION = "Graphics & UI Framework/Wayland Window System"
LICENSE = "MIT"
PV = "0.1.9"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by weston-ivi-shell-dev
PROVIDES += "weston-ivi-shell-dev"


#PROVIDES by weston-ivi-shell-config
PROVIDES += "weston-ivi-shell-config"


#PROVIDES by weston-ivi-shell-clients
PROVIDES += "weston-ivi-shell-clients"


#PROVIDES by weston-ivi-shell


RDEPENDS = ""
#RDEPENDS of weston-ivi-shell-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "weston-ivi-shell"

#RDEPENDS of weston-ivi-shell-config (${PN}-config)
RDEPENDS_${PN}-config += "weekeyboard"
RDEPENDS_${PN}-config += "weston-ivi-shell"
RDEPENDS_${PN}-config += "genivi-shell"

#RDEPENDS of weston-ivi-shell (${PN})
RDEPENDS_${PN} += "weston"


DEPENDS = ""
#DEPENDS of weston-ivi-shell
DEPENDS += "virtual/egl"
DEPENDS += "mtdev"
DEPENDS += "libxkbcommon"
DEPENDS += "libjpeg-turbo"
inherit pkgconfig
DEPENDS_append_class-native = " automake-native"
DEPENDS_append_class-target = " automake-native"
DEPENDS += "weston"
DEPENDS += "wayland"
DEPENDS_append_class-native = " libtool"
DEPENDS_append_class-target = " libtool-cross"
DEPENDS += "cairo"
DEPENDS += "pango"
DEPENDS_append_class-native = " autoconf-native"
DEPENDS_append_class-target = " autoconf-native"
DEPENDS += "pixman"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/weston-ivi-shell.manifest .
 
 
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
  
  # We only care about the ivi-shell related bits so disable anything
  # unrelated.
  
   
  autotools_do_configure
  
  oe_runmake ${PARALLEL_MAKE}
  
  
  
  
}
EXTRA_OECONF += " --disable-static --disable-libunwind --disable-xwayland --disable-xwayland-test --disable-drm-compositor --disable-x11-compositor --disable-rpi-compositor --disable-fbdev-compositor --disable-wayland-compositor --disable-headless-compositor --disable-weston-launch --enable-simple-clients --enable-clients --disable-wcap-tools --enable-demo-clients-install --disable-libinput-backend --disable-fullscreen-shell --disable-desktop-shell --disable-simple-clients --enable-ivi-shell"

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
 
 # install example clients
 mkdir -p ${D}${prefix}/bin/ivi
 #mv ${D}${prefix}/bin/weston-calibrator ${D}${prefix}/bin/ivi
 #mv ${D}${prefix}/bin/weston-simple-touch ${D}${prefix}/bin/ivi
 #mv ${D}${prefix}/bin/weston-simple-shm ${D}${prefix}/bin/ivi
 mv ${D}${prefix}/bin/weston-simple-egl ${D}${prefix}/bin/ivi
 mv ${D}${prefix}/bin/weston-flower ${D}${prefix}/bin/ivi
 mv ${D}${prefix}/bin/weston-image ${D}${prefix}/bin/ivi
 mv ${D}${prefix}/bin/weston-cliptest ${D}${prefix}/bin/ivi
 mv ${D}${prefix}/bin/weston-dnd ${D}${prefix}/bin/ivi
 mv ${D}${prefix}/bin/weston-editor ${D}${prefix}/bin/ivi
 mv ${D}${prefix}/bin/weston-smoke ${D}${prefix}/bin/ivi
 mv ${D}${prefix}/bin/weston-resizor ${D}${prefix}/bin/ivi
 mv ${D}${prefix}/bin/weston-eventdemo ${D}${prefix}/bin/ivi
 mv ${D}${prefix}/bin/weston-clickdot ${D}${prefix}/bin/ivi
 mv ${D}${prefix}/bin/weston-subsurfaces ${D}${prefix}/bin/ivi
 mv ${D}${prefix}/bin/weston-transformed ${D}${prefix}/bin/ivi
 mv ${D}${prefix}/bin/weston-fullscreen ${D}${prefix}/bin/ivi
 mv ${D}${prefix}/bin/weston-terminal ${D}${prefix}/bin/ivi
 
 install -d ${D}${prefix}/share/weston-ivi-shell/protocol/
 
 install -m 644 protocol/*.xml \
     ${D}${prefix}/share/weston-ivi-shell/protocol/
 
 install -m 644 protocol/*.h \
     ${D}${prefix}/share/weston-ivi-shell/protocol/
 
 install -m 644 protocol/*.c \
     ${D}${prefix}/share/weston-ivi-shell/protocol/
 
 mkdir -p ${D}${sysconfdir}/xdg/weston
 install -m 0644 ${S}/packaging/weston.ini ${D}${sysconfdir}/xdg/weston
 install -d ${D}${prefix}/share/weston/
 
 
 
 
}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " weston-ivi-shell-dev "
PACKAGES += " weston-ivi-shell-config "
PACKAGES += " weston-ivi-shell-clients "
PACKAGES += " weston-ivi-shell "

weston-ivi-shell-dev_files = ""
weston-ivi-shell-dev_files += "${prefix}/include/weston/ivi-layout-export.h"
weston-ivi-shell-dev_files += "${prefix}/include/weston/ivi-layout-private.h"
weston-ivi-shell-dev_files += "${prefix}/include/weston/ivi-shell.h"
weston-ivi-shell-dev_files += "${prefix}/include/weston/ivi-shell-ext.h"
weston-ivi-shell-dev_files += "${prefix}/share/weston-ivi-shell/protocol/*"
MANIFESTFILES_${PN}-dev = "weston-ivi-shell.manifest"

weston-ivi-shell-config_files = ""
weston-ivi-shell-config_files += "${sysconfdir}/xdg/weston/weston.ini"
CONFFILES_${PN}-config = ""
CONFFILES_${PN}-config += "${sysconfdir}/xdg/weston/weston.ini"
MANIFESTFILES_${PN}-config = "weston-ivi-shell.manifest"

weston-ivi-shell-clients_files = ""
weston-ivi-shell-clients_files += "${prefix}/bin/ivi/weston-simple-egl"
weston-ivi-shell-clients_files += "${prefix}/bin/ivi/weston-flower"
weston-ivi-shell-clients_files += "${prefix}/bin/ivi/weston-image"
weston-ivi-shell-clients_files += "${prefix}/bin/ivi/weston-cliptest"
weston-ivi-shell-clients_files += "${prefix}/bin/ivi/weston-dnd"
weston-ivi-shell-clients_files += "${prefix}/bin/ivi/weston-editor"
weston-ivi-shell-clients_files += "${prefix}/bin/ivi/weston-smoke"
weston-ivi-shell-clients_files += "${prefix}/bin/ivi/weston-resizor"
weston-ivi-shell-clients_files += "${prefix}/bin/ivi/weston-eventdemo"
weston-ivi-shell-clients_files += "${prefix}/bin/ivi/weston-clickdot"
weston-ivi-shell-clients_files += "${prefix}/bin/ivi/weston-subsurfaces"
weston-ivi-shell-clients_files += "${prefix}/bin/ivi/weston-transformed"
weston-ivi-shell-clients_files += "${prefix}/bin/ivi/weston-fullscreen"
weston-ivi-shell-clients_files += "${prefix}/bin/ivi/weston-terminal"
MANIFESTFILES_${PN}-clients = "weston-ivi-shell.manifest"

weston-ivi-shell_files = ""
weston-ivi-shell_files += "${prefix}/lib/weston/ivi-shell.so"
weston-ivi-shell_files += "${prefix}/lib/weston/ivi-layout.so"
weston-ivi-shell_files += "${prefix}/lib/weston/hmi-controller.so"
weston-ivi-shell_files += "${prefix}/libexec/weston-ivi-shell-user-interface"
weston-ivi-shell_files += "${prefix}/share/weston/*"
MANIFESTFILES_${PN} = "weston-ivi-shell.manifest"

FILES_${PN}-dev = "${weston-ivi-shell-dev_files}"
FILES_${PN}-config = "${weston-ivi-shell-config_files}"
FILES_${PN}-clients = "${weston-ivi-shell-clients_files}"
FILES_${PN} = "${weston-ivi-shell_files}"

PKG_weston-ivi-shell-dev= "weston-ivi-shell-dev"
PKG_weston-ivi-shell-config= "weston-ivi-shell-config"
PKG_weston-ivi-shell-clients= "weston-ivi-shell-clients"
PKG_weston-ivi-shell= "weston-ivi-shell"

require weston-ivi-shell-extraconf.inc

