DESCRIPTION = "GUPnP-AV is a collection of helpers for building UPnP AV applications"
HOMEPAGE = "http://nohomepage.org"
SECTION = "System/Libraries"
LICENSE = "LGPLv2+"
PV = "0.12.4"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by gupnp-av-dev
PROVIDES += "gupnp-av-dev"


#PROVIDES by gupnp-av


RDEPENDS = ""
#RDEPENDS of gupnp-av-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "gupnp-av"

#RDEPENDS of gupnp-av (${PN})
RDEPENDS_${PN} += "glibc"


DEPENDS = ""
#DEPENDS of gupnp-av
DEPENDS += "libxml2"
inherit pkgconfig
DEPENDS += "glib-2.0"
DEPENDS += "gupnp"
DEPENDS += "vala"
DEPENDS += "gtk-doc-stub"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q -n gupnp-av-0.12.4
 
 
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
 
 rm -rf  $RPM_BUILD_ROOT${prefix}/share/gtk-doc
 
 
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
PACKAGES += " gupnp-av-dev "
PACKAGES += " gupnp-av "

gupnp-av-dev_files = ""
gupnp-av-dev_files += "${prefix}/include/gupnp-av-1.0/libgupnp-av"
gupnp-av-dev_files += "${prefix}/lib/*.so"
gupnp-av-dev_files += "${prefix}/lib/pkgconfig/gupnp-av-1.0.pc"
gupnp-av-dev_files += "${prefix}/lib/girepository-1.0/GUPnPAV-1.0.typelib"
gupnp-av-dev_files += "${prefix}/share/gir-1.0/GUPnPAV-1.0.gir"
gupnp-av-dev_files += "${prefix}/share/vala/vapi/gupnp-av-1.0.deps"
gupnp-av-dev_files += "${prefix}/share/vala/vapi/gupnp-av-1.0.vapi"

gupnp-av_files = ""
gupnp-av_files += "AUTHORS COPYING README"
gupnp-av_files += "${prefix}/lib/*.so.*"
gupnp-av_files += "${prefix}/share/gupnp-av/*.xsd"

FILES_${PN}-dev = "${gupnp-av-dev_files}"
FILES_${PN} = "${gupnp-av_files}"

PKG_gupnp-av-dev= "gupnp-av-dev"
PKG_gupnp-av= "gupnp-av"

require gupnp-av-extraconf.inc

