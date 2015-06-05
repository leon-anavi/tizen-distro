DESCRIPTION = "Library providing support for "XML Signature" and "XML Encryption" standards"
HOMEPAGE = "http://www.aleksey.com/xmlsec/index.html"
SECTION = "System/Libraries"
LICENSE = "MIT"
PV = "1.2.19"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by xmlsec1


#PROVIDES by xmlsec1-dev-static
PROVIDES += "xmlsec1-dev-static"


#PROVIDES by xmlsec1-gcrypt
PROVIDES += "xmlsec1-gcrypt"


#PROVIDES by xmlsec1-openssl
PROVIDES += "xmlsec1-openssl"


#PROVIDES by xmlsec1-dev
PROVIDES += "xmlsec1-dev"


RDEPENDS = ""
#RDEPENDS of xmlsec1-dev-static (${PN}-dev-static)
RDEPENDS_${PN}-dev-static += "xmlsec1-dev"

#RDEPENDS of xmlsec1-gcrypt (${PN}-gcrypt)
RDEPENDS_${PN}-gcrypt += "xmlsec1"

#RDEPENDS of xmlsec1-openssl (${PN}-openssl)
RDEPENDS_${PN}-openssl += "xmlsec1"

#RDEPENDS of xmlsec1-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "xmlsec1"


DEPENDS = ""
#DEPENDS of xmlsec1
DEPENDS += "openssl"
DEPENDS += "libxml2"
DEPENDS_append_class-native = " fdupes-native"
DEPENDS_append_class-target = " fdupes-native"
inherit pkgconfig
DEPENDS += "libxslt"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/xmlsec1.manifest .
 
 
 
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
EXTRA_OECONF += " --enable-static --enable-dynamic --disable-crypto-dl --disable-apps-crypto-dl --without-gnutls"

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
   
 
 
   rm -rf ${D}${infodir} 
   rm -rf ${D}${prefix}/share/doc/packages 
   rm -rf ${D}${prefix}/share/doc/xmlsec1 
   rm -rf ${D}${prefix}/share/doc/xmlsec1-1.2.19 
   rm -rf ${D}${prefix}/share/gtk-doc 
   rm -rf ${D}${prefix}/share/doc 
   rm -rf ${D}${prefix}/share/man 
   find ${D} -regex ".*/man/man./.*.[0-9]" | xargs rm -f -- 
   find ${D} -regex ".*/man/../man./.*.[0-9]" | xargs rm -f -- 
   find ${D} -regex ".*/man/man./.*.[0-9]pm" | xargs rm -f --
 
 #fdupes ${D}
 
 
}

pkg_postinst_${PN}() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postinst_${PN}() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postinst_${PN}() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_${PN}() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_${PN}() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_${PN}() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " xmlsec1 "
PACKAGES += " xmlsec1-dev-static "
PACKAGES += " xmlsec1-gcrypt "
PACKAGES += " xmlsec1-openssl "
PACKAGES += " xmlsec1-dev "

xmlsec1_files = ""
xmlsec1_files += "Copyright"
xmlsec1_files += "${prefix}/lib/libxmlsec1.so.*"
xmlsec1_files += "${prefix}/bin/xmlsec1"
MANIFESTFILES_${PN} = "xmlsec1.manifest"

xmlsec1-dev-static_files = ""
xmlsec1-dev-static_files += "${prefix}/lib/*.a"
MANIFESTFILES_${PN}-dev-static = "xmlsec1.manifest"

xmlsec1-gcrypt_files = ""
xmlsec1-gcrypt_files += "${prefix}/lib/libxmlsec1-gcrypt.so.*"
MANIFESTFILES_${PN}-gcrypt = "xmlsec1.manifest"

xmlsec1-openssl_files = ""
xmlsec1-openssl_files += "${prefix}/lib/libxmlsec1-openssl.so.*"
MANIFESTFILES_${PN}-openssl = "xmlsec1.manifest"

xmlsec1-dev_files = ""
xmlsec1-dev_files += "Copyright"
xmlsec1-dev_files += "${prefix}/include/xmlsec1"
xmlsec1-dev_files += "${prefix}/bin/xmlsec1-config"
xmlsec1-dev_files += "${prefix}/lib/lib*.so"
xmlsec1-dev_files += "${prefix}/lib/pkgconfig/*"
xmlsec1-dev_files += "${prefix}/lib/xmlsec1Conf.sh"
xmlsec1-dev_files += "${prefix}/share/aclocal/xmlsec1.m4"
MANIFESTFILES_${PN}-dev = "xmlsec1.manifest"

FILES_${PN} = "${xmlsec1_files}"
FILES_${PN}-dev-static = "${xmlsec1-dev-static_files}"
FILES_${PN}-gcrypt = "${xmlsec1-gcrypt_files}"
FILES_${PN}-openssl = "${xmlsec1-openssl_files}"
FILES_${PN}-dev = "${xmlsec1-dev_files}"

PKG_xmlsec1= "xmlsec1"
PKG_xmlsec1-dev-static= "xmlsec1-dev-static"
PKG_xmlsec1-gcrypt= "xmlsec1-gcrypt"
PKG_xmlsec1-openssl= "xmlsec1-openssl"
PKG_xmlsec1-dev= "xmlsec1-dev"

require xmlsec1-extraconf.inc

