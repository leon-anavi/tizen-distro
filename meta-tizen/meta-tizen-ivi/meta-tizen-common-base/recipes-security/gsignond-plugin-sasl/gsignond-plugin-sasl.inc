DESCRIPTION = "SASL plugin for GLib"
HOMEPAGE = "http://nohomepage.org"
SECTION = "Security/Accounts"
LICENSE = "LGPL-2.1+"
PV = "1.0.0"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by gsignond-plugin-sasl-doc
PROVIDES += "gsignond-plugin-sasl-doc"


#PROVIDES by gsignond-plugin-sasl


RDEPENDS = ""
#RDEPENDS of gsignond-plugin-sasl-doc (${PN}-doc)
RDEPENDS_${PN}-doc += "gsignond-plugin-sasl"

#RDEPENDS of gsignond-plugin-sasl (${PN})
RDEPENDS_${PN} += "glibc"


DEPENDS = ""
#DEPENDS of gsignond-plugin-sasl
DEPENDS += "gsignond"
DEPENDS += "libgsasl"
inherit pkgconfig
DEPENDS += "glib-2.0"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q -n gsignond-plugin-sasl-1.0.0
 cp ${S}/packaging/gsignond-plugin-sasl.manifest .
 
 
 
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
PACKAGES += " gsignond-plugin-sasl "

gsignond-plugin-sasl-doc_files = ""
gsignond-plugin-sasl-doc_files += "${prefix}/share/gtk-doc/html/gsignond-plugin-sasl/*"

gsignond-plugin-sasl_files = ""
gsignond-plugin-sasl_files += "${prefix}/lib/gsignond/gplugins/libsasl*.so"
MANIFESTFILES_${PN} = "gsignond-plugin-sasl.manifest"

FILES_${PN}-doc = "${gsignond-plugin-sasl-doc_files}"
FILES_${PN} = "${gsignond-plugin-sasl_files}"

PKG_gsignond-plugin-sasl-doc= "gsignond-plugin-sasl-doc"
PKG_gsignond-plugin-sasl= "gsignond-plugin-sasl"

require gsignond-plugin-sasl-extraconf.inc

