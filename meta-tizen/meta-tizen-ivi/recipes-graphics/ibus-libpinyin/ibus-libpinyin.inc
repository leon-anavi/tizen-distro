DESCRIPTION = "Intelligent Pinyin engine based on libpinyin for IBus"
HOMEPAGE = "http://nohomepage.org"
SECTION = "System/Libraries"
LICENSE = "GPL-2.0+"
PV = "1.6.92"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by ibus-libpinyin


RDEPENDS = ""
#RDEPENDS of ibus-libpinyin (${PN})
RDEPENDS_${PN} += "libpinyin"
RDEPENDS_${PN} += "ibus"


DEPENDS = ""
#DEPENDS of ibus-libpinyin
DEPENDS_append_class-native = " intltool-native"
DEPENDS_append_class-target = " intltool-native"
DEPENDS += "libpinyin"
inherit pkgconfig
#Replace "DEPENDS" on gettext by "inherit gettext"
inherit gettext
DEPENDS += "ibus"
DEPENDS += "lua"
DEPENDS_append_class-native = " libtool"
DEPENDS_append_class-target = " libtool-cross"
DEPENDS += "sqlite3"
DEPENDS += "util-linux"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/ibus-libpinyin.manifest .
 
 
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
EXTRA_OECONF += " --disable-static --disable-boost"

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
 
 #find_lang ibus-libpinyin
 
 
}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " ibus-libpinyin "

ibus-libpinyin_files = ""
ibus-libpinyin_files += "AUTHORS README"
ibus-libpinyin_files += "${prefix}/share/applications/*.desktop"
ibus-libpinyin_files += "${prefix}/libexec/ibus-engine-libpinyin"
ibus-libpinyin_files += "${prefix}/libexec/ibus-setup-libpinyin"
ibus-libpinyin_files += "${prefix}/share/ibus-libpinyin/phrases.txt"
ibus-libpinyin_files += "${prefix}/share/ibus-libpinyin/icons"
ibus-libpinyin_files += "${prefix}/share/ibus-libpinyin/setup"
ibus-libpinyin_files += "${prefix}/share/ibus-libpinyin/*.lua"
ibus-libpinyin_files += "${prefix}/share/ibus-libpinyin/db/*.db"
ibus-libpinyin_files += "${prefix}/share/ibus-libpinyin"
ibus-libpinyin_files += "${prefix}/share/ibus-libpinyin/db"
ibus-libpinyin_files += "${prefix}/share/ibus/component/*"
MANIFESTFILES_${PN} = "ibus-libpinyin.manifest"
DIRFILES_${PN} = ""
DIRFILES_${PN} += "${prefix}/share/ibus-libpinyin"
DIRFILES_${PN} += "${prefix}/share/ibus-libpinyin/db"

FILES_${PN} = "${ibus-libpinyin_files}"

PKG_ibus-libpinyin= "ibus-libpinyin"

require ibus-libpinyin-extraconf.inc

