DESCRIPTION = "Samba Trivial Database"
HOMEPAGE = "http://tdb.samba.org/"
SECTION = "System/Libraries"
LICENSE = "GPL-3.0+"
PV = "1.3.1"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by libtdb-dev
PROVIDES += "libtdb-dev"


#PROVIDES by tdb


#PROVIDES by libtdb
PROVIDES += "libtdb"


#PROVIDES by python-tdb
PROVIDES += "python-tdb"


#PROVIDES by tdb-tools
PROVIDES += "tdb-tools"


RDEPENDS = ""
#RDEPENDS of libtdb-dev (lib${PN}-dev)
RDEPENDS_lib${PN}-dev += "libtdb"
RDEPENDS_lib${PN}-dev += "pkgconfig"

#RDEPENDS of libtdb (lib${PN})
RDEPENDS_lib${PN} += "glibc"
RDEPENDS_lib${PN} += "pkgconfig"


DEPENDS = ""
#DEPENDS of tdb
inherit pythonnative
DEPENDS_append_class-native = " autoconf-native"
DEPENDS_append_class-target = " autoconf-native"
inherit pkgconfig

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -n tdb-1.3.1 -q
 cp ${S}/packaging/tdb.manifest .
 
 
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
  #--disable-python
  
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
 
 
   oe_runmake \
         DESTDIR=${D} \
         INSTALL_ROOT=${D} \
         BINDIR=${prefix}/bin \
   install  
   rm -f ${D}${infodir}/dir 
   find ${D} -regex ".*\.la$" | xargs rm -f -- 
   find ${D} -regex ".*\.a$" | xargs rm -f --
 
 
 
}

pkg_postinst_libtdb() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_libtdb() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " libtdb-dev "
PACKAGES += " tdb-tools "
PACKAGES += " libtdb "
PACKAGES += " python-tdb "

libtdb-dev_files = ""
libtdb-dev_files += "${prefix}/include/tdb.h"
libtdb-dev_files += "${prefix}/lib/libtdb.so"
libtdb-dev_files += "${prefix}/lib/pkgconfig/tdb.pc"
MANIFESTFILES_lib${PN}-dev = "tdb.manifest"

tdb-tools_files = ""
tdb-tools_files += "${prefix}/bin/tdbbackup"
tdb-tools_files += "${prefix}/bin/tdbdump"
tdb-tools_files += "${prefix}/bin/tdbrestore"
tdb-tools_files += "${prefix}/bin/tdbtool"
MANIFESTFILES_${PN}-tools = "tdb.manifest"

libtdb_files = ""
libtdb_files += "${prefix}/lib/libtdb.so.*"
MANIFESTFILES_lib${PN} = "tdb.manifest"

python-tdb_files = ""
python-tdb_files += "${prefix}/lib/python2.7/site-packages/tdb.so"
MANIFESTFILES_python-${PN} = "tdb.manifest"

FILES_lib${PN}-dev = "${libtdb-dev_files}"
FILES_${PN}-tools = "${tdb-tools_files}"
FILES_lib${PN} = "${libtdb_files}"
FILES_python-${PN} = "${python-tdb_files}"

PKG_libtdb-dev= "libtdb-dev"
PKG_tdb-tools= "tdb-tools"
PKG_libtdb= "libtdb"
PKG_python-tdb= "python-tdb"

require tdb-extraconf.inc

