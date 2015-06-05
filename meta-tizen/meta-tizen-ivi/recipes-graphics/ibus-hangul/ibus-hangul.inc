DESCRIPTION = "The Hangul engine for IBus input platform"
HOMEPAGE = "http://nohomepage.org"
SECTION = "System/Libraries"
LICENSE = "GPL-2.0+"
PV = "1.4.2"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by ibus-hangul


RDEPENDS = ""
#RDEPENDS of ibus-hangul (${PN})
RDEPENDS_${PN} += "ibus"


DEPENDS = ""
#DEPENDS of ibus-hangul
DEPENDS_append_class-native = " intltool-native"
DEPENDS_append_class-target = " intltool-native"
inherit pkgconfig
#Replace "DEPENDS" on gettext by "inherit gettext"
inherit gettext
DEPENDS += "ibus"
DEPENDS_append_class-native = " libtool"
DEPENDS_append_class-target = " libtool-cross"
DEPENDS += "libhangul"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/ibus-hangul.manifest .
 
 
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
  # make -C po update-gmo
  oe_runmake ${PARALLEL_MAKE}
  
  
  
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
 oe_runmake DESTDIR=${D} install
 
 rm -f ${D}${prefix}/bin/ibus-setup-hangul
 sed -i 's!^Exec=ibus-setup-hangul!Exec=${prefix}/libexec/ibus-setup-hangul!' ${D}${prefix}/share/applications/ibus-setup-hangul.desktop
 
 #find_lang ibus-hangul
 
 
}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " ibus-hangul "

ibus-hangul_files = ""
ibus-hangul_files += "AUTHORS README"
ibus-hangul_files += "${prefix}/libexec/ibus-engine-hangul"
ibus-hangul_files += "${prefix}/libexec/ibus-setup-hangul"
ibus-hangul_files += "${prefix}/share/ibus-hangul"
ibus-hangul_files += "${prefix}/share/ibus/component/*"
ibus-hangul_files += "${prefix}/lib/ibus-hangul/setup/*"
ibus-hangul_files += "${prefix}/share/applications/ibus-setup-hangul.desktop"
ibus-hangul_files += "${prefix}/share/icons/hicolor/*/apps/*"
MANIFESTFILES_${PN} = "ibus-hangul.manifest"

FILES_${PN} = "${ibus-hangul_files}"

PKG_ibus-hangul= "ibus-hangul"

require ibus-hangul-extraconf.inc

