DESCRIPTION = "Evolution Data Server"
HOMEPAGE = "http://www.gnome.org"
SECTION = "Development/Libraries"
LICENSE = "LGPL-2.0+"
PV = "3.11.93"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by evolution-data-server


#PROVIDES by libedataserver
PROVIDES += "libedataserver"


#PROVIDES by libecal
PROVIDES += "libecal"


#PROVIDES by libcamel
PROVIDES += "libcamel"


#PROVIDES by libedata-cal
PROVIDES += "libedata-cal"


#PROVIDES by libebook-contacts
PROVIDES += "libebook-contacts"


#PROVIDES by libedata-book
PROVIDES += "libedata-book"


#PROVIDES by evolution-data-server-doc
PROVIDES += "evolution-data-server-doc"


#PROVIDES by libebook
PROVIDES += "libebook"


#PROVIDES by libebackend
PROVIDES += "libebackend"


#PROVIDES by evolution-data-server-dev
PROVIDES += "evolution-data-server-dev"


RDEPENDS = ""
#RDEPENDS of evolution-data-server (${PN})
RDEPENDS_${PN} += "glib-2.0"

#RDEPENDS of evolution-data-server-doc (${PN}-doc)
RDEPENDS_${PN}-doc += "evolution-data-server"

#RDEPENDS of evolution-data-server-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "evolution-data-server"
RDEPENDS_${PN}-dev += "libedataserver"
RDEPENDS_${PN}-dev += "libecal"
RDEPENDS_${PN}-dev += "glibc"
RDEPENDS_${PN}-dev += "libcamel"
RDEPENDS_${PN}-dev += "libedata-cal"
RDEPENDS_${PN}-dev += "libedata-book"
RDEPENDS_${PN}-dev += "libebook"
RDEPENDS_${PN}-dev += "libebackend"


DEPENDS = ""
#DEPENDS of evolution-data-server
DEPENDS_append_class-native = " intltool-native"
DEPENDS_append_class-target = " intltool-native"
DEPENDS += "glibc-locale"
DEPENDS += "gnome-common"
DEPENDS += "gperf"
DEPENDS += "nss"
DEPENDS += "vala"
DEPENDS += "db"
#Replace "DEPENDS" on gettext by "inherit gettext"
inherit gettext
inherit pkgconfig
DEPENDS += "libsoup-2.4"
inherit pythonnative
DEPENDS += "gcr"
DEPENDS += "libsecret"
DEPENDS += "icu"
DEPENDS += "sqlite3"
DEPENDS_append_class-native = " fdupes-native"
DEPENDS_append_class-target = " fdupes-native"
DEPENDS += "libical"
DEPENDS += "gtk-doc"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/evolution-data-server.manifest .
 
 
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
  
  
  # "maintainer mode" depends on GTK and is not needed
  # for packaging, so disable it.
  
  
   
  autotools_do_configure
  
  oe_runmake ${PARALLEL_MAKE} V=1
  
  
  
}
EXTRA_OECONF += " --libexecdir=${prefix}/libexec/evolution-data-server --disable-maintainer-mode --enable-ipv6= --enable-smime= --enable-nntp= --disable-static --disable-uoa --enable-goa=no --enable-weather=no --enable-gtk=no --enable-google=no --disable-vala-bindings --disable-introspection --disable-examples"

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
 mkdir -p ${D}${prefix}/share/help
 find ${D} -name evolution-data-server-3.11.mo -execdir mv {} evolution-data-server.mo \;
 #find_lang evolution-data-server
 #fdupes ${D}
 
 #lang_package
 
 
}

pkg_postinst_libebook() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postinst_libecal() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postinst_libedata-cal() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postinst_${PN}() {
    #!/bin/sh -e

    %glib2_gsettings_schema_post

}

pkg_postinst_libebackend() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postinst_libebook-contacts() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postinst_libedataserver() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postinst_libedata-book() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postinst_libcamel() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_libedata-cal() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_libcamel() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_libedata-book() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_libebackend() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_${PN}() {
    #!/bin/sh -e

    %glib2_gsettings_schema_postun

}

pkg_postrm_libedataserver() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_libecal() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_libebook() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_libebook-contacts() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " evolution-data-server "
PACKAGES += " libedataserver "
PACKAGES += " libecal "
PACKAGES += " libcamel "
PACKAGES += " libedata-cal "
PACKAGES += " libebook-contacts "
PACKAGES += " libebook "
PACKAGES += " libedata-book "
PACKAGES += " libebackend "
PACKAGES += " evolution-data-server-dev "

evolution-data-server_files = ""
evolution-data-server_files += "${prefix}/share/GConf/gsettings/evolution-data-server.convert"
evolution-data-server_files += "${prefix}/share/GConf/gsettings/libedataserver.convert"
evolution-data-server_files += "${prefix}/share/glib-2.0/schemas/org.gnome.Evolution.DefaultSources.gschema.xml"
evolution-data-server_files += "${prefix}/share/glib-2.0/schemas/org.gnome.evolution.eds-shell.gschema.xml"
evolution-data-server_files += "${prefix}/share/glib-2.0/schemas/org.gnome.evolution.shell.network-config.gschema.xml"
evolution-data-server_files += "${prefix}/share/glib-2.0/schemas/org.gnome.evolution-data-server.addressbook.gschema.xml"
evolution-data-server_files += "${prefix}/share/glib-2.0/schemas/org.gnome.evolution-data-server.calendar.gschema.xml"
evolution-data-server_files += "${prefix}/share/pixmaps/evolution-data-server/"
evolution-data-server_files += "${prefix}/share/dbus-1/services/org.gnome.evolution.dataserver.*.service"
evolution-data-server_files += "${prefix}/lib/evolution-data-server/"
evolution-data-server_files += "${prefix}/libexec/evolution-data-server/"
MANIFESTFILES_${PN} = "evolution-data-server.manifest"

libedataserver_files = ""
libedataserver_files += "${prefix}/lib/libedataserver-1.2.so.17*"
MANIFESTFILES_libedataserver = "evolution-data-server.manifest"

libecal_files = ""
libecal_files += "${prefix}/lib/libecal-1.2.so.15*"
MANIFESTFILES_libecal = "evolution-data-server.manifest"

libcamel_files = ""
libcamel_files += "${prefix}/lib/libcamel-1.2.so.43*"
MANIFESTFILES_libcamel = "evolution-data-server.manifest"

libedata-cal_files = ""
libedata-cal_files += "${prefix}/lib/libedata-cal-1.2.so.20*"
MANIFESTFILES_libedata-cal = "evolution-data-server.manifest"

libebook-contacts_files = ""
libebook-contacts_files += "${prefix}/lib/libebook-contacts-1.2.so.0*"
MANIFESTFILES_libebook-contacts = "evolution-data-server.manifest"

libebook_files = ""
libebook_files += "${prefix}/lib/libebook-1.2.so.14*"
MANIFESTFILES_libebook = "evolution-data-server.manifest"

libedata-book_files = ""
libedata-book_files += "${prefix}/lib/libedata-book-1.2.so.17*"
MANIFESTFILES_libedata-book = "evolution-data-server.manifest"

libebackend_files = ""
libebackend_files += "${prefix}/lib/libebackend-1.2.so.6*"
MANIFESTFILES_libebackend = "evolution-data-server.manifest"

evolution-data-server-dev_files = ""
evolution-data-server-dev_files += "${prefix}/include/evolution-data-server/"
evolution-data-server-dev_files += "${prefix}/lib/*.so"
evolution-data-server-dev_files += "${prefix}/lib/pkgconfig/*.pc"
MANIFESTFILES_${PN}-dev = "evolution-data-server.manifest"

FILES_${PN} = "${evolution-data-server_files}"
FILES_libedataserver = "${libedataserver_files}"
FILES_libecal = "${libecal_files}"
FILES_libcamel = "${libcamel_files}"
FILES_libedata-cal = "${libedata-cal_files}"
FILES_libebook-contacts = "${libebook-contacts_files}"
FILES_libebook = "${libebook_files}"
FILES_libedata-book = "${libedata-book_files}"
FILES_libebackend = "${libebackend_files}"
FILES_${PN}-dev = "${evolution-data-server-dev_files}"

PKG_evolution-data-server= "evolution-data-server"
PKG_libedataserver= "libedataserver"
PKG_libecal= "libecal"
PKG_libcamel= "libcamel"
PKG_libedata-cal= "libedata-cal"
PKG_libebook-contacts= "libebook-contacts"
PKG_libebook= "libebook"
PKG_libedata-book= "libedata-book"
PKG_libebackend= "libebackend"
PKG_evolution-data-server-dev= "evolution-data-server-dev"

require evolution-data-server-extraconf.inc

