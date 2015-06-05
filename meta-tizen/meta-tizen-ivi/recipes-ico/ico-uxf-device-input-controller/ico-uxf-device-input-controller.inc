DESCRIPTION = "Device Input Controller"
HOMEPAGE = "http://nohomepage.org"
SECTION = "Graphics & UI Framework/Input"
LICENSE = "Apache-2.0"
PV = "0.9.06"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by ico-uxf-device-input-controller


RDEPENDS = ""
#RDEPENDS of ico-uxf-device-input-controller (${PN})
RDEPENDS_${PN} += "weston"
RDEPENDS_${PN} += "ico-uxf-utilities"
RDEPENDS_${PN} += "ico-uxf-weston-plugin"


DEPENDS = ""
#DEPENDS of ico-uxf-device-input-controller
DEPENDS += "ico-uxf-utilities"
DEPENDS += "virtual/egl"
inherit pkgconfig
DEPENDS += "glib-2.0"
DEPENDS += "wayland"
DEPENDS += "virtual/libgl"
DEPENDS += "virtual/libgles2"
DEPENDS += "ico-uxf-weston-plugin"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q -n ico-uxf-device-input-controller-0.9.06
 
 
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
 
 # configurations
 mkdir -p ${D}/opt/etc/ico/device-input-controller
 mkdir -p ${D}${prefix}/lib/systemd/user
 install -m 0644 settings/drivingforcegt.conf ${D}/opt/etc/ico/device-input-controller
 install -m 0644 settings/g27racingwheel.conf ${D}/opt/etc/ico/device-input-controller
 install -m 0755 settings/set_daynight.sh ${D}/opt/etc/ico/device-input-controller
 install -m 644 settings/ico-device-input-controller.service ${D}${prefix}/lib/systemd/user/ico-device-input-controller.service
 
 
}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " ico-uxf-device-input-controller "

ico-uxf-device-input-controller_files = ""
ico-uxf-device-input-controller_files += "${prefix}/bin/ico_dic-gtforce"
ico-uxf-device-input-controller_files += "/opt/etc/ico/device-input-controller/drivingforcegt.conf"
ico-uxf-device-input-controller_files += "/opt/etc/ico/device-input-controller/g27racingwheel.conf"
ico-uxf-device-input-controller_files += "/opt/etc/ico/device-input-controller/set_daynight.sh"
ico-uxf-device-input-controller_files += "${prefix}/lib/systemd/user/ico-device-input-controller.service"
MANIFESTFILES_${PN} = "ico-uxf-device-input-controller.manifest"

FILES_${PN} = "${ico-uxf-device-input-controller_files}"

PKG_ico-uxf-device-input-controller= "ico-uxf-device-input-controller"

require ico-uxf-device-input-controller-extraconf.inc

