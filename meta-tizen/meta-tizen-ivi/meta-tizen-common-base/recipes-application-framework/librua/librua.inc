DESCRIPTION = "Recently used application"
HOMEPAGE = "http://nohomepage.org"
SECTION = "Application Framework/Libraries"
LICENSE = "Apache-2.0"
PV = "0.1.0"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by librua


#PROVIDES by librua-dev
PROVIDES += "librua-dev"


#PROVIDES by librua-test
PROVIDES += "librua-test"


RDEPENDS = ""
#RDEPENDS of librua-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "librua"

#RDEPENDS of librua-test (${PN}-test)
RDEPENDS_${PN}-test += "librua"


DEPENDS = ""
#DEPENDS of librua
DEPENDS += "sqlite3"
DEPENDS += "tizen-platform-config"
inherit tizen_cmake
inherit pkgconfig
DEPENDS += "libslp-db-util"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/librua.manifest .
 
 
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
 
 
   cmake \
         -DCMAKE_VERBOSE_MAKEFILE=ON \
         -DCMAKE_INSTALL_PREFIX:PATH=${prefix} \
         -DCMAKE_INSTALL_LIBDIR:PATH=${prefix}/lib \
         -DINCLUDE_INSTALL_DIR:PATH=${prefix}/include \
         -DLIB_INSTALL_DIR:PATH=${prefix}/lib \
         -DSYSCONF_INSTALL_DIR:PATH=${sysconfdir} \
         -DSHARE_INSTALL_PREFIX:PATH=${prefix}/share \
         -DCMAKE_SKIP_RPATH:BOOL=ON \
         -DBUILD_SHARED_LIBS:BOOL=ON \
         -DCMAKE_TOOLCHAIN_FILE=${WORKDIR}/toolchain.cmake \
         ${EXTRA_OECMAKE} .
 make ${PARALLEL_MAKE}
 
 
 
}

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

pkg_postinst_${PN}() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_${PN}() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " librua "
PACKAGES += " librua-dev "
PACKAGES += " librua-test "

librua_files = ""
librua_files += "${prefix}/lib/librua.so.*"
MANIFESTFILES_${PN} = "librua.manifest"

librua-dev_files = ""
librua-dev_files += "${prefix}/include/rua"
librua-dev_files += "${prefix}/include/rua/*.h"
librua-dev_files += "${prefix}/lib/librua.so"
librua-dev_files += "${prefix}/lib/pkgconfig/rua.pc"
MANIFESTFILES_${PN}-dev = "librua.manifest"
DIRFILES_${PN}-dev = ""
DIRFILES_${PN}-dev += "${prefix}/include/rua"

librua-test_files = ""
librua-test_files += "${prefix}/bin/rua-test"
MANIFESTFILES_${PN}-test = "librua.manifest"

FILES_${PN} = "${librua_files}"
FILES_${PN}-dev = "${librua-dev_files}"
FILES_${PN}-test = "${librua-test_files}"

PKG_librua= "librua"
PKG_librua-dev= "librua-dev"
PKG_librua-test= "librua-test"

require librua-extraconf.inc

