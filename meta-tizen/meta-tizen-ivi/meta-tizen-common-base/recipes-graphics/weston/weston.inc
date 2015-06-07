DESCRIPTION = "Wayland Compositor Infrastructure"
HOMEPAGE = "http://weston.freedesktop.org/"
SECTION = "Graphics & UI Framework/Wayland Window System"
LICENSE = "MIT"
PV = "1.6.0"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by weston


#PROVIDES by weston-dev
PROVIDES += "weston-dev"


#PROVIDES by weston-docs
PROVIDES += "weston-docs "


#PROVIDES by weston-clients
PROVIDES += "weston-clients"


RDEPENDS = ""
#RDEPENDS of weston (${PN})
RDEPENDS_${PN} += "shadow"
RDEPENDS_${PN} += "tlm"


DEPENDS = ""
#DEPENDS of weston
DEPENDS += "mtdev"
DEPENDS += "cairo"
DEPENDS += "expat"
DEPENDS += "udev"
DEPENDS += "libvpx"
DEPENDS += "xz"
DEPENDS += "libinput"
DEPENDS_append_class-native = " automake-native"
DEPENDS_append_class-target = " automake-native"
DEPENDS += "mesa"
DEPENDS += "systemd"
inherit pkgconfig
DEPENDS += "glib-2.0"
DEPENDS += "wayland"
DEPENDS += "pixman"
DEPENDS += "libdrm"
DEPENDS_append_class-native = " libtool"
DEPENDS_append_class-target = " libtool-cross"
DEPENDS += "libffi"
DEPENDS += "pango"
DEPENDS += "poppler"
DEPENDS += "virtual/libgles2"
DEPENDS += "libpam"
DEPENDS += "virtual/egl"
DEPENDS += "libxkbcommon"
DEPENDS += "libjpeg-turbo"
DEPENDS_append_class-native = " autoconf-native"
DEPENDS_append_class-target = " autoconf-native"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/weston.manifest .
 
 
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
  
  make ${PARALLEL_MAKE}
  
  
  
}
EXTRA_OECONF += " --disable-static --disable-setuid-install --enable-simple-clients --enable-clients --disable-libunwind --disable-xwayland --disable-xwayland-test --disable-x11-compositor --disable-rpi-compositor --with-cairo=glesv2 "

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
 install -m 755 weston-calibrator ${D}${prefix}/bin
 install -m 755 weston-simple-touch ${D}${prefix}/bin
 install -m 755 weston-simple-shm ${D}${prefix}/bin
 install -m 755 weston-simple-egl ${D}${prefix}/bin
 install -m 755 weston-simple-damage ${D}${prefix}/bin
 install -m 755 weston-nested-client ${D}${prefix}/bin
 install -m 755 weston-nested ${D}${prefix}/bin
 install -m 755 weston-flower ${D}${prefix}/bin
 install -m 755 weston-image ${D}${prefix}/bin
 install -m 755 weston-cliptest ${D}${prefix}/bin
 install -m 755 weston-dnd ${D}${prefix}/bin
 install -m 755 weston-editor ${D}${prefix}/bin
 install -m 755 weston-stacking ${D}${prefix}/bin
 install -m 755 weston-smoke ${D}${prefix}/bin
 install -m 755 weston-scaler ${D}${prefix}/bin
 install -m 755 weston-resizor ${D}${prefix}/bin
 install -m 755 weston-eventdemo ${D}${prefix}/bin
 install -m 755 weston-clickdot ${D}${prefix}/bin
 install -m 755 weston-subsurfaces ${D}${prefix}/bin
 install -m 755 weston-transformed ${D}${prefix}/bin
 install -m 755 weston-fullscreen ${D}${prefix}/bin
 
 
}

pkg_preinst_${PN}() {
    #!/bin/sh -e

    getent group weston-launch >/dev/null || $D${prefix}/sbin/groupadd -o -r weston-launch

}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " weston "
PACKAGES += " weston-clients "
PACKAGES += " weston-docs "
PACKAGES += " weston-dev "

weston_files = ""
weston_files += "${prefix}/bin/wcap-*"
weston_files += "${prefix}/bin/weston"
weston_files += "${prefix}/bin/weston-info"
weston_files += "${prefix}/bin/weston-launch"
weston_files += "${prefix}/bin/weston-terminal"
weston_files += "${prefix}/libexec/weston-*"
weston_files += "${prefix}/lib/weston/desktop-shell.so"
weston_files += "${prefix}/lib/weston/drm-backend.so"
weston_files += "${prefix}/lib/weston/fbdev-backend.so"
weston_files += "${prefix}/lib/weston/fullscreen-shell.so"
weston_files += "${prefix}/lib/weston/headless-backend.so"
weston_files += "${prefix}/lib/weston/wayland-backend.so"
weston_files += "${prefix}/lib/weston/gl-renderer.so"
weston_files += "${prefix}/share/weston"
MANIFESTFILES_${PN} = "weston.manifest"

weston-clients_files = ""
weston-clients_files += "${prefix}/bin/weston-simple-touch"
weston-clients_files += "${prefix}/bin/weston-simple-shm"
weston-clients_files += "${prefix}/bin/weston-simple-egl"
weston-clients_files += "${prefix}/bin/weston-simple-damage"
weston-clients_files += "${prefix}/bin/weston-nested-client"
weston-clients_files += "${prefix}/bin/weston-nested"
weston-clients_files += "${prefix}/bin/weston-flower"
weston-clients_files += "${prefix}/bin/weston-image"
weston-clients_files += "${prefix}/bin/weston-cliptest"
weston-clients_files += "${prefix}/bin/weston-dnd"
weston-clients_files += "${prefix}/bin/weston-editor"
weston-clients_files += "${prefix}/bin/weston-stacking"
weston-clients_files += "${prefix}/bin/weston-smoke"
weston-clients_files += "${prefix}/bin/weston-scaler"
weston-clients_files += "${prefix}/bin/weston-resizor"
weston-clients_files += "${prefix}/bin/weston-eventdemo"
weston-clients_files += "${prefix}/bin/weston-clickdot"
weston-clients_files += "${prefix}/bin/weston-subsurfaces"
weston-clients_files += "${prefix}/bin/weston-transformed"
weston-clients_files += "${prefix}/bin/weston-fullscreen"
weston-clients_files += "${prefix}/bin/weston-calibrator"
MANIFESTFILES_${PN}-clients = "weston.manifest"

weston-docs_files = ""

weston-dev_files = ""
weston-dev_files += "${prefix}/include/weston/*.h"
weston-dev_files += "${prefix}/lib/pkgconfig/*.pc"
MANIFESTFILES_${PN}-dev = "weston.manifest"

FILES_${PN} = "${weston_files}"
FILES_${PN}-clients = "${weston-clients_files}"
FILES_${PN}-docs = "${weston-docs_files}"
FILES_${PN}-dev = "${weston-dev_files}"

PKG_weston= "weston"
PKG_weston-clients= "weston-clients"
PKG_weston-docs= "weston-docs"
PKG_weston-dev= "weston-dev"

require weston-extraconf.inc

