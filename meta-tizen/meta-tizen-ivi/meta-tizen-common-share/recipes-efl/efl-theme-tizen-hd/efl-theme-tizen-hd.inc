DESCRIPTION = "Tizen theme files"
HOMEPAGE = "http://nohomepage.org"
SECTION = "System/Libraries"
LICENSE = "Apache-2.0"
PV = "1.0.204r07"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by efl-theme-tizen-dev
PROVIDES += "efl-theme-tizen-dev"


#PROVIDES by efl-theme-tizen-hd


RDEPENDS = ""

DEPENDS = ""
#DEPENDS of efl-theme-tizen-hd
DEPENDS += "efl"
inherit perlnative

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
 
 export CFLAGS="${CFLAGS} --fPIC"
 export LDFLAGS="${LDFLAGS} -Wl,--hash-style=both -Wl,--as-needed -Wl,--rpath=${prefix}/lib"
 
 oe_runmake ${PARALLEL_MAKE}
 
 
 
 
}

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
 mkdir -p ${D}${prefix}/share/license
 cp ${WORKDIR}/git/LICENSE ${D}${prefix}/share/license/efl-theme-tizen-hd
 cp ${D}${prefix}/share/elementary/themes/tizen-HD-dark.edj ${D}${prefix}/share/elementary/themes/tizen-hd.edj
 
 
}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " efl-theme-tizen-dev "
PACKAGES += " efl-theme-tizen-hd "

efl-theme-tizen-dev_files = ""
efl-theme-tizen-dev_files += "/opt/var/efl-theme-tizen-edc/*"

efl-theme-tizen-hd_files = ""
efl-theme-tizen-hd_files += "${prefix}/share/elementary/themes/tizen-HD-dark.edj"
efl-theme-tizen-hd_files += "${prefix}/share/elementary/themes/tizen-HD-light.edj"
efl-theme-tizen-hd_files += "${prefix}/share/elementary/themes/tizen-hd.edj"
efl-theme-tizen-hd_files += "${prefix}/share/license/efl-theme-tizen-hd"
MANIFESTFILES_${PN} = "efl-theme-tizen-hd.manifest"

FILES_efl-theme-tizen-dev = "${efl-theme-tizen-dev_files}"
FILES_${PN} = "${efl-theme-tizen-hd_files}"

PKG_efl-theme-tizen-dev= "efl-theme-tizen-dev"
PKG_efl-theme-tizen-hd= "efl-theme-tizen-hd"

require efl-theme-tizen-hd-extraconf.inc

