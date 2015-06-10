DESCRIPTION = "Utility library for easing DLNA-related tasks"
HOMEPAGE = "http://nohomepage.org"
SECTION = "Applications/Multimedia"
LICENSE = "LGPLv2.1"
PV = "0.10.2"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by gupnp-dlna-dev
PROVIDES += "gupnp-dlna-dev"


#PROVIDES by gupnp-dlna


RDEPENDS = ""
#RDEPENDS of gupnp-dlna-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "gupnp-dlna"

#RDEPENDS of gupnp-dlna (${PN})
RDEPENDS_${PN} += "glibc"


DEPENDS = ""
#DEPENDS of gupnp-dlna
DEPENDS += "libxml2"
DEPENDS += "vala"
inherit pkgconfig
DEPENDS += "glib-2.0"
DEPENDS += "gstreamer1.0-plugins-base"
DEPENDS += "gstreamer1.0"
DEPENDS += "gtk-doc-stub"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q -n gupnp-dlna-0.10.2
 
 
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
EXTRA_OECONF += " --disable-static "

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
PACKAGES += " gupnp-dlna-dev "
PACKAGES += " gupnp-dlna "

gupnp-dlna-dev_files = ""
gupnp-dlna-dev_files += "${prefix}/include/gupnp-dlna-2.0/libgupnp-dlna/gupnp-dlna.h"
gupnp-dlna-dev_files += "${prefix}/include/gupnp-dlna-2.0/libgupnp-dlna/gupnp-dlna-audio-information.h"
gupnp-dlna-dev_files += "${prefix}/include/gupnp-dlna-2.0/libgupnp-dlna/gupnp-dlna-container-information.h"
gupnp-dlna-dev_files += "${prefix}/include/gupnp-dlna-2.0/libgupnp-dlna/gupnp-dlna-gst-utils.h"
gupnp-dlna-dev_files += "${prefix}/include/gupnp-dlna-2.0/libgupnp-dlna/gupnp-dlna-g-values.h"
gupnp-dlna-dev_files += "${prefix}/include/gupnp-dlna-2.0/libgupnp-dlna/gupnp-dlna-image-information.h"
gupnp-dlna-dev_files += "${prefix}/include/gupnp-dlna-2.0/libgupnp-dlna/gupnp-dlna-information.h"
gupnp-dlna-dev_files += "${prefix}/include/gupnp-dlna-2.0/libgupnp-dlna/gupnp-dlna-profile.h"
gupnp-dlna-dev_files += "${prefix}/include/gupnp-dlna-2.0/libgupnp-dlna/gupnp-dlna-profile-guesser.h"
gupnp-dlna-dev_files += "${prefix}/include/gupnp-dlna-2.0/libgupnp-dlna/gupnp-dlna-restriction.h"
gupnp-dlna-dev_files += "${prefix}/include/gupnp-dlna-2.0/libgupnp-dlna/gupnp-dlna-value-list.h"
gupnp-dlna-dev_files += "${prefix}/include/gupnp-dlna-2.0/libgupnp-dlna/gupnp-dlna-values.h"
gupnp-dlna-dev_files += "${prefix}/include/gupnp-dlna-2.0/libgupnp-dlna/gupnp-dlna-video-information.h"
gupnp-dlna-dev_files += "${prefix}/include/gupnp-dlna-2.0/libgupnp-dlna/metadata/gupnp-dlna-metadata-extractor.h"
gupnp-dlna-dev_files += "${prefix}/lib/pkgconfig/gupnp-dlna-2.0.pc"
gupnp-dlna-dev_files += "${prefix}/lib/pkgconfig/gupnp-dlna-metadata-2.0.pc"
gupnp-dlna-dev_files += "${prefix}/lib/pkgconfig/gupnp-dlna-gst-2.0.pc"
gupnp-dlna-dev_files += "${prefix}/lib/libgupnp-dlna-2.0.so"
gupnp-dlna-dev_files += "${prefix}/lib/libgupnp-dlna-gst-2.0.so"
gupnp-dlna-dev_files += "${prefix}/lib/gupnp-dlna/libgstreamer.so"
gupnp-dlna-dev_files += "${prefix}/lib/girepository-1.0/GUPnPDLNA-2.0.typelib"
gupnp-dlna-dev_files += "${prefix}/lib/girepository-1.0/GUPnPDLNAGst-2.0.typelib"
gupnp-dlna-dev_files += "${prefix}/share/gir-1.0/GUPnPDLNA-2.0.gir"
gupnp-dlna-dev_files += "${prefix}/share/gir-1.0/GUPnPDLNAGst-2.0.gir"
gupnp-dlna-dev_files += "${prefix}/share/vala/vapi/gupnp-dlna-2.0.deps"
gupnp-dlna-dev_files += "${prefix}/share/vala/vapi/gupnp-dlna-2.0.vapi"
gupnp-dlna-dev_files += "${prefix}/share/vala/vapi/gupnp-dlna-gst-2.0.deps"
gupnp-dlna-dev_files += "${prefix}/share/vala/vapi/gupnp-dlna-gst-2.0.vapi"

gupnp-dlna_files = ""
gupnp-dlna_files += "${prefix}/bin/gupnp-dlna-info-2.0"
gupnp-dlna_files += "${prefix}/bin/gupnp-dlna-ls-profiles-2.0"
gupnp-dlna_files += "${prefix}/lib/libgupnp-dlna-2.0.so.*"
gupnp-dlna_files += "${prefix}/lib/libgupnp-dlna-gst-2.0.so.*"
gupnp-dlna_files += "${prefix}/lib/gupnp-dlna/libgstreamer.so"
gupnp-dlna_files += "${prefix}/share/gupnp-dlna-2.0/dlna-profiles/aac.xml"
gupnp-dlna_files += "${prefix}/share/gupnp-dlna-2.0/dlna-profiles/ac3.xml"
gupnp-dlna_files += "${prefix}/share/gupnp-dlna-2.0/dlna-profiles/amr.xml"
gupnp-dlna_files += "${prefix}/share/gupnp-dlna-2.0/dlna-profiles/avc.xml"
gupnp-dlna_files += "${prefix}/share/gupnp-dlna-2.0/dlna-profiles/common.xml"
gupnp-dlna_files += "${prefix}/share/gupnp-dlna-2.0/dlna-profiles/dlna-profiles.rng"
gupnp-dlna_files += "${prefix}/share/gupnp-dlna-2.0/dlna-profiles/jpeg.xml"
gupnp-dlna_files += "${prefix}/share/gupnp-dlna-2.0/dlna-profiles/lpcm.xml"
gupnp-dlna_files += "${prefix}/share/gupnp-dlna-2.0/dlna-profiles/mp3.xml"
gupnp-dlna_files += "${prefix}/share/gupnp-dlna-2.0/dlna-profiles/mpeg-ts.xml"
gupnp-dlna_files += "${prefix}/share/gupnp-dlna-2.0/dlna-profiles/mpeg1.xml"
gupnp-dlna_files += "${prefix}/share/gupnp-dlna-2.0/dlna-profiles/mpeg4.xml"
gupnp-dlna_files += "${prefix}/share/gupnp-dlna-2.0/dlna-profiles/png.xml"
gupnp-dlna_files += "${prefix}/share/gupnp-dlna-2.0/dlna-profiles/wma.xml"
gupnp-dlna_files += "${prefix}/share/gupnp-dlna-2.0/dlna-profiles/mpeg-common.xml"
gupnp-dlna_files += "${prefix}/share/gupnp-dlna-2.0/dlna-profiles/mpeg-ps.xml"

FILES_${PN}-dev = "${gupnp-dlna-dev_files}"
FILES_${PN} = "${gupnp-dlna_files}"

PKG_gupnp-dlna-dev= "gupnp-dlna-dev"
PKG_gupnp-dlna= "gupnp-dlna"

require gupnp-dlna-extraconf.inc

