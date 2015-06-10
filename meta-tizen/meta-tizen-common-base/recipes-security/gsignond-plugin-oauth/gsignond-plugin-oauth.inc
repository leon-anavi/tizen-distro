DESCRIPTION = "OAuth plugin for GLib"
HOMEPAGE = "http://nohomepage.org"
SECTION = "Security/Accounts"
LICENSE = "LGPL-2.1+"
PV = "1.0.0"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by gsignond-plugin-oauth


#PROVIDES by gsignond-plugin-oauth-doc
PROVIDES += "gsignond-plugin-oauth-doc"


RDEPENDS = ""
#RDEPENDS of gsignond-plugin-oauth (${PN})
RDEPENDS_${PN} += "glibc"

#RDEPENDS of gsignond-plugin-oauth-doc (${PN}-doc)
RDEPENDS_${PN}-doc += "gsignond-plugin-oauth"


DEPENDS = ""
#DEPENDS of gsignond-plugin-oauth
DEPENDS += "gsignond"
inherit pkgconfig
DEPENDS += "glib-2.0"
DEPENDS += "libsoup-2.4"
DEPENDS += "json-glib"
DEPENDS += "gnutls"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q -n gsignond-plugin-oauth-1.0.0
 cp ${S}/packaging/gsignond-plugin-oauth.manifest .
 
 
 
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
PACKAGES += " gsignond-plugin-oauth "

gsignond-plugin-oauth_files = ""
gsignond-plugin-oauth_files += "${prefix}/lib/gsignond/gplugins/liboauth*.so"
MANIFESTFILES_${PN} = "gsignond-plugin-oauth.manifest"

gsignond-plugin-oauth-doc_files = ""
gsignond-plugin-oauth-doc_files += "${prefix}/share/gtk-doc/html/gsignond-plugin-oauth/*"

FILES_${PN} = "${gsignond-plugin-oauth_files}"
FILES_${PN}-doc = "${gsignond-plugin-oauth-doc_files}"

PKG_gsignond-plugin-oauth= "gsignond-plugin-oauth"
PKG_gsignond-plugin-oauth-doc= "gsignond-plugin-oauth-doc"

require gsignond-plugin-oauth-extraconf.inc

