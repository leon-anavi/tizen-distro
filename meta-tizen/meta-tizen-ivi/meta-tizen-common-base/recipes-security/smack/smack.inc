DESCRIPTION = "Selection of tools for developers working with Smack"
HOMEPAGE = "http://nohomepage.org"
SECTION = "Security/Access Control"
LICENSE = "LGPL-2.1"
PV = "1.0.5"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by smack-dev
PROVIDES += "smack-dev"


#PROVIDES by smack


#PROVIDES by libsmack
PROVIDES += "libsmack"


#PROVIDES by smack-docs
PROVIDES += "smack-docs "


RDEPENDS = ""
#RDEPENDS of smack-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "smack"


DEPENDS = ""
#DEPENDS of smack
DEPENDS_append_class-native = " autoconf-native"
DEPENDS_append_class-target = " autoconf-native"
DEPENDS_append_class-native = " libtool"
DEPENDS_append_class-target = " libtool-cross"
inherit pkgconfig
DEPENDS_append_class-native = " automake-native"
DEPENDS_append_class-target = " automake-native"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/smack.manifest .
 
 
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
EXTRA_OECONF += " --with-systemdsystemunitdir=${systemd_unitdir}/system"

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
 install -d ${D}${sysconfdir}/smack/accesses.d
 install -d ${D}${sysconfdir}/smack/cipso.d
 install -d ${D}${sysconfdir}/smack/netlabel.d
 
 
}

pkg_postinst_libsmack() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_libsmack() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " smack-dev "
PACKAGES += " smack "
PACKAGES += " libsmack "
PACKAGES += " smack-docs "

smack-dev_files = ""
smack-dev_files += "${prefix}/include/sys/smack.h"
smack-dev_files += "${prefix}/lib/libsmack.so"
smack-dev_files += "${prefix}/lib/pkgconfig/libsmack.pc"
MANIFESTFILES_${PN}-dev = "smack.manifest"

smack_files = ""
smack_files += "${sysconfdir}/smack"
smack_files += "${sysconfdir}/smack/accesses.d"
smack_files += "${sysconfdir}/smack/cipso.d"
smack_files += "${sysconfdir}/smack/netlabel.d"
smack_files += "${prefix}/bin/*"
MANIFESTFILES_${PN} = "smack.manifest"

libsmack_files = ""
libsmack_files += "${prefix}/lib/libsmack.so.*"
MANIFESTFILES_lib${PN} = "smack.manifest"

smack-docs_files = ""

FILES_${PN}-dev = "${smack-dev_files}"
FILES_${PN} = "${smack_files}"
FILES_lib${PN} = "${libsmack_files}"
FILES_${PN}-docs = "${smack-docs_files}"

PKG_smack-dev= "smack-dev"
PKG_smack= "smack"
PKG_libsmack= "libsmack"
PKG_smack-docs= "smack-docs"

require smack-extraconf.inc

