DESCRIPTION = "ALSA Scenario pkg"
HOMEPAGE = "http://nohomepage.org"
SECTION = "Multimedia/Audio FW"
LICENSE = "LGPL-2.0+"
PV = "0.2.1"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by alsa-scenario-dev
PROVIDES += "alsa-scenario-dev"


#PROVIDES by alsa-scenario


RDEPENDS = ""
#RDEPENDS of alsa-scenario-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "alsa-scenario"

#RDEPENDS of alsa-scenario (${PN})
RDEPENDS_${PN} += "glibc"


DEPENDS = ""
#DEPENDS of alsa-scenario
DEPENDS += "alsa-lib"
inherit pkgconfig

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/alsa-scenario.manifest .
 
 
 
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
  
  cp -f ${prefix}/share/libtool/config/config.guess ${WORKDIR}/alsa-scenario-0.2.1/
  cp -f ${prefix}/share/libtool/config/config.sub ${WORKDIR}/alsa-scenario-0.2.1/
  
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
 
 rm -rf ${D}
 
   oe_runmake \
         DESTDIR=${D} \
         INSTALL_ROOT=${D} \
         BINDIR=${prefix}/bin \
   install  
   rm -f ${D}${infodir}/dir 
   find ${D} -regex ".*\.la$" | xargs rm -f -- 
   find ${D} -regex ".*\.a$" | xargs rm -f --
 
 
 
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
PACKAGES += " alsa-scenario-dev "
PACKAGES += " alsa-scenario "

alsa-scenario-dev_files = ""
alsa-scenario-dev_files += "${prefix}/include/alsa/*.h"
alsa-scenario-dev_files += "${prefix}/lib/libascenario.so"
alsa-scenario-dev_files += "${prefix}/lib/pkgconfig/libascenario.pc"
MANIFESTFILES_${PN}-dev = "alsa-scenario.manifest"

alsa-scenario_files = ""
alsa-scenario_files += "${prefix}/lib/libascenario-0.2.so.*"
MANIFESTFILES_${PN} = "alsa-scenario.manifest"

FILES_${PN}-dev = "${alsa-scenario-dev_files}"
FILES_${PN} = "${alsa-scenario_files}"

PKG_alsa-scenario-dev= "alsa-scenario-dev"
PKG_alsa-scenario= "alsa-scenario"

require alsa-scenario-extraconf.inc

