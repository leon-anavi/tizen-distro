DESCRIPTION = "Virtual Keyboard Application"
HOMEPAGE = "http://github.com/etrunko/weekeyboard"
SECTION = "Graphics & UI Framework/Libraries"
LICENSE = "Apache-2.0"
PV = "0.0.3"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by weekeyboard


RDEPENDS = ""
#RDEPENDS of weekeyboard (${PN})
RDEPENDS_${PN} += "ibus-hangul"
RDEPENDS_${PN} += "ibus"
RDEPENDS_${PN} += "ibus-libpinyin"


DEPENDS = ""
#DEPENDS of weekeyboard
DEPENDS += "edje"
DEPENDS += "ibus"
DEPENDS += "evas"
inherit pkgconfig
DEPENDS += "efreet"
DEPENDS += "eina"
DEPENDS += "eet"
DEPENDS += "ecore"
DEPENDS += "eldbus"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/weekeyboard.manifest .
 
 
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
 
 
}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " weekeyboard "

weekeyboard_files = ""
weekeyboard_files += "${prefix}/bin/weekeyboard"
weekeyboard_files += "${prefix}/share/weekeyboard/*.edj"
weekeyboard_files += "${prefix}/share/X11/xkb/symbols/wkb"
MANIFESTFILES_${PN} = "weekeyboard.manifest"

FILES_${PN} = "${weekeyboard_files}"

PKG_weekeyboard= "weekeyboard"

require weekeyboard-extraconf.inc

