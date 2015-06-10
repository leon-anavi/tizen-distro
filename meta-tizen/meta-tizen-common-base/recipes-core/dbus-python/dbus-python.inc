DESCRIPTION = "Python bindings for D-Bus"
HOMEPAGE = "http://www.freedesktop.org/wiki/Software/DBusBindings/"
SECTION = "System/Libraries"
LICENSE = "MIT"
PV = "1.2.0"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by dbus-python-dev
PROVIDES += "dbus-python-dev"


#PROVIDES by dbus-python


RDEPENDS = ""
#RDEPENDS of dbus-python-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "dbus-python"

#RDEPENDS of dbus-python (${PN})
RDEPENDS_${PN} += "python-xml"


DEPENDS = ""
#DEPENDS of dbus-python
inherit pythonnative
DEPENDS += "dbus"
DEPENDS_append_class-native = " fdupes-native"
DEPENDS_append_class-target = " fdupes-native"
inherit pkgconfig
DEPENDS += "dbus-glib"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/dbus-python.manifest .
 
 
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
  
  export CFLAGS="$CFLAGS -fstack-protector -fno-strict-aliasing -fPIC"
  
  autotools_do_configure
  oe_runmake ${PARALLEL_MAKE}
  
  
  
}
EXTRA_OECONF += " --docdir=${prefix}/share/doc/packages/dbus-python"

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
 
 
 
   rm -rf ${D}${infodir} 
   rm -rf ${D}${prefix}/share/doc/packages 
   rm -rf ${D}${prefix}/share/doc/dbus-python 
   rm -rf ${D}${prefix}/share/doc/dbus-python-1.2.0 
   rm -rf ${D}${prefix}/share/gtk-doc 
   rm -rf ${D}${prefix}/share/doc 
   rm -rf ${D}${prefix}/share/man 
   find ${D} -regex ".*/man/man./.*.[0-9]" | xargs rm -f -- 
   find ${D} -regex ".*/man/../man./.*.[0-9]" | xargs rm -f -- 
   find ${D} -regex ".*/man/man./.*.[0-9]pm" | xargs rm -f --
 #fdupes -s ${D}
 
 
 
}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " dbus-python-dev "
PACKAGES += " dbus-python "

dbus-python-dev_files = ""
dbus-python-dev_files += "${prefix}/include/dbus-1.0/dbus/dbus-python.h"
dbus-python-dev_files += "${prefix}/lib/pkgconfig/dbus-python.pc"
MANIFESTFILES_${PN}-dev = "dbus-python.manifest"

dbus-python_files = ""
dbus-python_files += "${prefix}/lib/python2.7/site-packages/*"
dbus-python_files += "${prefix}/lib/python2.7/site-packages/*"
MANIFESTFILES_${PN} = "dbus-python.manifest"

FILES_${PN}-dev = "${dbus-python-dev_files}"
FILES_${PN} = "${dbus-python_files}"

PKG_dbus-python-dev= "dbus-python-dev"
PKG_dbus-python= "dbus-python"

require dbus-python-extraconf.inc

