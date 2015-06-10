DESCRIPTION = "CarSimulator"
HOMEPAGE = "http://nohomepage.org"
SECTION = "Automotive/ICO Homescreen"
LICENSE = "Apache-2.0"
PV = "0.9.10"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by ico-vic-carsimulator


RDEPENDS = ""
#RDEPENDS of ico-vic-carsimulator (${PN})
RDEPENDS_${PN} += "ico-vic-amb-plugin"
RDEPENDS_${PN} += "glibc"
RDEPENDS_${PN} += "ico-uxf-utilities"


DEPENDS = ""
#DEPENDS of ico-vic-carsimulator
DEPENDS += "ico-uxf-utilities"
DEPENDS += "make"
inherit pkgconfig
DEPENDS += "glib-2.0"
DEPENDS += "json-glib"
DEPENDS_append_class-native = " automake-native"
DEPENDS_append_class-target = " automake-native"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q -n ico-vic-carsimulator-0.9.10
 
 
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
 mkdir -p ${D}${sysconfdir}/ico-vic-carsim/
 mkdir -p ${D}${prefix}/lib/systemd/user
 install -m 0644 G25.conf ${D}${sysconfdir}/ico-vic-carsim/
 install -m 0644 G27.conf ${D}${sysconfdir}/ico-vic-carsim/
 install -m 0644 ico-vic-carsim.service ${D}${prefix}/lib/systemd/user/ico-vic-carsim.service
 
 
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
PACKAGES += " ico-vic-carsimulator "

ico-vic-carsimulator_files = ""
ico-vic-carsimulator_files += "${prefix}/bin/ico-vic-carsim"
ico-vic-carsimulator_files += "${prefix}/bin/*"
ico-vic-carsimulator_files += "${sysconfdir}/ico-vic-carsim/*"
ico-vic-carsimulator_files += "${prefix}/lib/systemd/user/ico-vic-carsim.service"
CONFFILES_${PN} = ""
CONFFILES_${PN} += "${sysconfdir}/ico-vic-carsim/*"
MANIFESTFILES_${PN} = "ico-vic-carsimulator.manifest"

FILES_${PN} = "${ico-vic-carsimulator_files}"

PKG_ico-vic-carsimulator= "ico-vic-carsimulator"

require ico-vic-carsimulator-extraconf.inc

