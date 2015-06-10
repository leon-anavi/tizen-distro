DESCRIPTION = "Intelligent Input Bus for Linux OS"
HOMEPAGE = "http://nohomepage.org"
SECTION = "System/Libraries"
LICENSE = "LGPL-2.0+"
PV = "1.5.4"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by ibus-dev
PROVIDES += "ibus-dev"


#PROVIDES by ibus-libs
PROVIDES += "ibus-libs"


#PROVIDES by ibus


RDEPENDS = ""
#RDEPENDS of ibus-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "dbus"
RDEPENDS_${PN}-dev += "ibus-libs"
RDEPENDS_${PN}-dev += "ibus"
RDEPENDS_${PN}-dev += "glib-2.0"

#RDEPENDS of ibus-libs (${PN}-libs)
RDEPENDS_${PN}-libs += "dbus"

#RDEPENDS of ibus (${PN})
RDEPENDS_${PN} += "ibus-libs"
RDEPENDS_${PN} += "python-pygobject"
RDEPENDS_${PN} += "dbus-python"
RDEPENDS_${PN} += "iso-codes"


DEPENDS = ""
#DEPENDS of ibus
DEPENDS_append_class-native = " intltool-native"
DEPENDS_append_class-target = " intltool-native"
DEPENDS += "python-pygobject"
DEPENDS += "iso-codes"
inherit pythonnative
DEPENDS += "vala"
DEPENDS += "libxkbcommon"
inherit pkgconfig
#Replace "DEPENDS" on gettext by "inherit gettext"
inherit gettext
DEPENDS += "wayland"
DEPENDS_append_class-native = " libtool"
DEPENDS_append_class-target = " libtool-cross"
DEPENDS += "gtk-doc-stub"
DEPENDS += "dbus-python"
DEPENDS_append_class-native = " fdupes-native"
DEPENDS_append_class-target = " fdupes-native"
DEPENDS += "dbus-glib"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/ibus.manifest .
 
 
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
EXTRA_OECONF += " --disable-static --disable-tests --disable-gtk2 --disable-gtk3 --disable-xim --enable-wayland --disable-vala --disable-gtk-doc --disable-gconf --disable-setup --disable-dconf --enable-python-library --disable-ui --disable-libnotify --enable-introspection"

do_install() {
 export RPM_BUILD_ROOT=${D}
 cd ${S}
 LANG=C
 export LANG
 unset DISPLAY
 rm -rf ${D}
 mkdir -p ${D}
 
 rm -rf ${D}
 make DESTDIR=${D} install
 rm -f ${D}${prefix}/lib/libibus-1.0.la
 
 rm -fr ${D}${prefix}/share/gtk-doc
 
 #find_lang ibus10
 
 #fdupes ${D}
 
 
}

pkg_postinst_${PN}() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postinst_${PN}() {
    #!/bin/sh -e

    # create registry cache
    [ -x $D${prefix}/bin/ibus ] && \
      $D${prefix}/bin/ibus write-cache --system &>/dev/null || :

}

pkg_postinst_${PN}() {
    #!/bin/sh -e

    # recreate icon cache
    touch --no-create $D${prefix}/share/icons/hicolor || :
    [ -x $D${prefix}/bin/gtk-update-icon-cache ] && \
      $D${prefix}/bin/gtk-update-icon-cache --quiet $D${prefix}/share/icons/hicolor || :

}

pkg_postrm_${PN}() {
    #!/bin/sh -e

    # recreate icon cache
    touch --no-create $D${prefix}/share/icons/hicolor || :
    [ -x $D${prefix}/bin/gtk-update-icon-cache ] && \
      $D${prefix}/bin/gtk-update-icon-cache --quiet $D${prefix}/share/icons/hicolor || :
    # 'ibus write-cache --system' updates the system cache.
    [ -f /var/cache/ibus/bus/registry ] && \
      rm /var/cache/ibus/bus/registry || :

}

pkg_postrm_${PN}() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " ibus-dev "
PACKAGES += " ibus-libs "
PACKAGES += " ibus "

ibus-dev_files = ""
ibus-dev_files += "${prefix}/lib/lib*.so"
ibus-dev_files += "${prefix}/lib/pkgconfig/*"
ibus-dev_files += "${prefix}/include/*"
ibus-dev_files += "${prefix}/share/gir-1.0/IBus-1.0.gir"
MANIFESTFILES_${PN}-dev = "ibus.manifest"

ibus-libs_files = ""
ibus-libs_files += "${prefix}/lib/libibus-1.0.so.*"
ibus-libs_files += "${prefix}/lib/girepository-1.0/IBus-1.0.typelib"
MANIFESTFILES_${PN}-libs = "ibus.manifest"

ibus_files = ""
ibus_files += "AUTHORS README"
ibus_files += "${prefix}/lib/python2.7/site-packages/ibus"
ibus_files += "${prefix}/lib/python2.7/site-packages/ibus/*"
ibus_files += "${prefix}/share/ibus/"
ibus_files += "${prefix}/bin/ibus"
ibus_files += "${prefix}/bin/ibus-daemon"
ibus_files += "${prefix}/share/ibus/keymaps/*"
ibus_files += "${prefix}/share/icons/hicolor/*/apps/*"
ibus_files += "${prefix}/libexec/*"
ibus_files += "${prefix}/share/ibus/component/simple.xml"
ibus_files += "${prefix}/share/bash-completion/completions/ibus.bash"
ibus_files += "${prefix}/share/man/man1/*"
MANIFESTFILES_${PN} = "ibus.manifest"
DIRFILES_${PN} = ""
DIRFILES_${PN} += "${prefix}/lib/python2.7/site-packages/ibus"
DIRFILES_${PN} += "${prefix}/share/ibus/"

FILES_${PN}-dev = "${ibus-dev_files}"
FILES_${PN}-libs = "${ibus-libs_files}"
FILES_${PN} = "${ibus_files}"

PKG_ibus-dev= "ibus-dev"
PKG_ibus-libs= "ibus-libs"
PKG_ibus= "ibus"

require ibus-extraconf.inc

