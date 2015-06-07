DESCRIPTION = "Wayland Test Suite"
HOMEPAGE = "https://github.com/01org/wayland-fits"
SECTION = "Applications/Core Applications"
LICENSE = "GPL-2.0+"
PV = "0.2.2"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by wayland-fits-master


RDEPENDS = ""

DEPENDS = ""
#DEPENDS of wayland-fits-master
DEPENDS += "libcheck"
DEPENDS += "libxkbcommon"
DEPENDS += "evas"
inherit pkgconfig
DEPENDS += "weston"
DEPENDS += "wayland"
DEPENDS += "unzip"
DEPENDS += "efl"
DEPENDS += "elementary"
DEPENDS += "ecore"
DEPENDS += "boost"
DEPENDS += "pixman"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 
 
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
  
  export CXXFLAGS="-DMEDIA_PATH='\"${prefix}/share/media\"'"
  ./autogen.sh
  
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
 mkdir -p -m 755 ${D}${prefix}/share/media
 install -m 755 ${S}/packaging/ADN_animation.gif ${D}${prefix}/share/media
 install -m 755 ${S}/packaging/bridge_of_the_gods.png ${D}${prefix}/share/media
 
 
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
PACKAGES += " wayland-fits-master "

wayland-fits-master_files = ""
wayland-fits-master_files += "${prefix}/bin/wfits"
wayland-fits-master_files += "${prefix}/lib/weston/weston-wfits.so"
wayland-fits-master_files += "${prefix}/share/media/*"
wayland-fits-master_files += "README"

FILES_${PN} = "${wayland-fits-master_files}"

PKG_wayland-fits-master= "wayland-fits-master"

require wayland-fits-master-extraconf.inc

