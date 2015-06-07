DESCRIPTION = "Stand-alone ini file parsing library"
HOMEPAGE = "http://ndevilla.free.fr/iniparser/"
SECTION = "System/Libraries"
LICENSE = "MIT"
PV = "2.17"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by iniparser-dev
PROVIDES += "iniparser-dev"


#PROVIDES by iniparser


RDEPENDS = ""
#RDEPENDS of iniparser-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "iniparser"


DEPENDS = ""

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/iniparser.manifest .
 
 
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
 
 make prefix=${prefix}  ${PARALLEL_MAKE} CFLAGS="$CFLAGS -fPIC"
 
 
 
}

do_install() {
 export RPM_BUILD_ROOT=${D}
 cd ${S}
 LANG=C
 export LANG
 unset DISPLAY
 rm -rf ${D}
 mkdir -p ${D}
 
 
 mkdir -p ${D}${prefix}/lib
 install -m 755 libiniparser.so.0 ${D}${prefix}/lib
 ln -s libiniparser.so.0 ${D}${prefix}/lib/libiniparser.so
 mkdir -p ${D}${prefix}/include
 install -m 644 src/*.h ${D}${prefix}/include
 install -m 644 src/*.h ${D}${prefix}/include
 mkdir -p ${D}${prefix}/lib/pkgconfig
 cat > ${D}${prefix}/lib/pkgconfig/iniparser.pc <<EOF
 prefix = ${prefix}
 exec_prefix = ${prefix}
 libdir = ${prefix}/lib
 includedir = ${prefix}/include
 
 Name : iniparser
 Description : a free stand-alone ini file parsing library.
 Version : 2.17
 Libs : -L\${libdir} -liniparser
 Cflags : -I\${includedir}
 
EOF
 
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
PACKAGES += " iniparser-dev "
PACKAGES += " iniparser "

iniparser-dev_files = ""
iniparser-dev_files += "${prefix}/include/*.h"
iniparser-dev_files += "${prefix}/lib/*.so"
iniparser-dev_files += "${prefix}/lib/pkgconfig/*.pc"
MANIFESTFILES_${PN}-dev = "iniparser.manifest"

iniparser_files = ""
iniparser_files += "${prefix}/lib/*.so.*"
MANIFESTFILES_${PN} = "iniparser.manifest"

FILES_${PN}-dev = "${iniparser-dev_files}"
FILES_${PN} = "${iniparser_files}"

PKG_iniparser-dev= "iniparser-dev"
PKG_iniparser= "iniparser"

require iniparser-extraconf.inc

