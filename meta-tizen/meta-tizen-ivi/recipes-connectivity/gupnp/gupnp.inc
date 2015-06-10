DESCRIPTION = "GUPnP is an framework for creating UPnP devices & control points"
HOMEPAGE = "http://nohomepage.org"
SECTION = "System/Libraries"
LICENSE = "LGPLv2+"
PV = "0.20.5"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by gupnp-dev
PROVIDES += "gupnp-dev"


#PROVIDES by gupnp


RDEPENDS = ""
#RDEPENDS of gupnp-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "gupnp"

#RDEPENDS of gupnp (${PN})
RDEPENDS_${PN} += "glibc"


DEPENDS = ""
#DEPENDS of gupnp
DEPENDS += "gssdp"
DEPENDS += "libxml2"
inherit pkgconfig
DEPENDS += "glib-2.0"
DEPENDS += "libsoup-2.4"
DEPENDS += "util-linux"
DEPENDS += "vala"
DEPENDS += "gtk-doc-stub"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q -n gupnp-0.20.5
 
 
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
PACKAGES += " gupnp-dev "
PACKAGES += " gupnp "

gupnp-dev_files = ""
gupnp-dev_files += "${prefix}/lib/pkgconfig/gupnp-1.0.pc"
gupnp-dev_files += "${prefix}/lib/*.so"
gupnp-dev_files += "${prefix}/include/gupnp-1.0"
gupnp-dev_files += "${prefix}/bin/gupnp-binding-tool"
gupnp-dev_files += "${prefix}/lib/girepository-1.0/GUPnP-1.0.typelib"
gupnp-dev_files += "${prefix}/share/gir-1.0/GUPnP-1.0.gir"
gupnp-dev_files += "${prefix}/share/vala/vapi/gupnp-1.0.deps"
gupnp-dev_files += "${prefix}/share/vala/vapi/gupnp-1.0.vapi"

gupnp_files = ""
gupnp_files += "${prefix}/lib/*.so.*"

FILES_${PN}-dev = "${gupnp-dev_files}"
FILES_${PN} = "${gupnp_files}"

PKG_gupnp-dev= "gupnp-dev"
PKG_gupnp= "gupnp"

require gupnp-extraconf.inc

