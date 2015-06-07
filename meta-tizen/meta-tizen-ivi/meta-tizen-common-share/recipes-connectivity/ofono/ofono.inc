DESCRIPTION = "Open Source Telephony"
HOMEPAGE = "http://ofono.org"
SECTION = "Telephony/Cellular"
LICENSE = "GPL-2.0"
PV = "1.15"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by ofono-docs
PROVIDES += "ofono-docs "


#PROVIDES by ofono-test
PROVIDES += "ofono-test"


#PROVIDES by ofono-dev
PROVIDES += "ofono-dev"


#PROVIDES by ofono


RDEPENDS = ""
#RDEPENDS of ofono-test (${PN}-test)
RDEPENDS_${PN}-test += "python-xml"
RDEPENDS_${PN}-test += "python-pygobject"
RDEPENDS_${PN}-test += "dbus-python"
RDEPENDS_${PN}-test += "ofono"

#RDEPENDS of ofono-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "ofono"

#RDEPENDS of ofono (${PN})
RDEPENDS_${PN} += "dbus"
RDEPENDS_${PN} += "systemd"


DEPENDS = ""
#DEPENDS of ofono
DEPENDS += "mobile-broadband-provider-info"
DEPENDS += "dbus"
DEPENDS += "glib-2.0"
inherit pkgconfig
DEPENDS += "udev"
DEPENDS_append_class-native = " automake-native"
DEPENDS_append_class-target = " automake-native"
DEPENDS += "bluez5"
DEPENDS_append_class-native = " libtool"
DEPENDS_append_class-target = " libtool-cross"
DEPENDS_append_class-native = " autoconf-native"
DEPENDS_append_class-target = " autoconf-native"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 
 cp ${S}/packaging/ofono.manifest .
 
 
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
  
  autoreconf --force --install
  
  
  autotools_do_configure
  
  make ${PARALLEL_MAKE}
  
  
  
}
EXTRA_OECONF += " --disable-static --enable-test --disable-bluez4 --with-systemdunitdir=${systemd_unitdir}/system"

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
 
 mkdir -p ${D}${prefix}/lib/systemd/system/network.target.wants
 ln -s ../ofono.service ${D}${prefix}/lib/systemd/system/network.target.wants/ofono.service
 
 
 mkdir -p ${D}/${systemd_unitdir}/system/multi-user.target.wants 
 ln -s ../ofono.service  ${D}/${systemd_unitdir}/system/multi-user.target.wants/ofono.service  
 
 
 
}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " ofono-test "
PACKAGES += " ofono-docs "
PACKAGES += " ofono-dev "
PACKAGES += " ofono "

ofono-test_files = ""
ofono-test_files += "${prefix}/lib/ofono/test/*"
MANIFESTFILES_${PN}-test = "ofono.manifest"

ofono-docs_files = ""

ofono-dev_files = ""
ofono-dev_files += "${prefix}/include/ofono/*.h"
ofono-dev_files += "${prefix}/lib/pkgconfig/ofono.pc"
MANIFESTFILES_${PN}-dev = "ofono.manifest"

ofono_files = ""
ofono_files += "${sysconfdir}/dbus-1/system.d/*.conf"
ofono_files += "${prefix}/sbin/*"
ofono_files += "${systemd_unitdir}/system/network.target.wants/ofono.service"
ofono_files += "${systemd_unitdir}/system/ofono.service"
ofono_files += "${systemd_unitdir}/system/multi-user.target.wants/ofono.service"
ofono_files += "${sysconfdir}/ofono/phonesim.conf"
CONFFILES_${PN} = ""
CONFFILES_${PN} += "${sysconfdir}/dbus-1/system.d/*.conf"
CONFFILES_${PN} += "${sysconfdir}/ofono/phonesim.conf"

FILES_${PN}-test = "${ofono-test_files}"
FILES_${PN}-docs = "${ofono-docs_files}"
FILES_${PN}-dev = "${ofono-dev_files}"
FILES_${PN} = "${ofono_files}"

PKG_ofono-test= "ofono-test"
PKG_ofono-docs= "ofono-docs"
PKG_ofono-dev= "ofono-dev"
PKG_ofono= "ofono"

require ofono-extraconf.inc

