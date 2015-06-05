DESCRIPTION = "Sensor framework common library"
HOMEPAGE = "http://nohomepage.org"
SECTION = "System/Sensor Framework"
LICENSE = "Apache-2.0"
PV = "0.3.20"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by libsf-common


#PROVIDES by libsf-common-dev
PROVIDES += "libsf-common-dev"


RDEPENDS = ""
#RDEPENDS of libsf-common-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "libsf-common"


DEPENDS = ""
#DEPENDS of libsf-common
inherit tizen_cmake
DEPENDS += "attr"
DEPENDS += "dlog"
inherit pkgconfig

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/libsf-common.manifest .
 
 
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
 
 mkdir -p ${D}${prefix}/share/license
 cp LICENSE ${D}${prefix}/share/license/libsf-common
 
 
}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " libsf-common "
PACKAGES += " libsf-common-dev "

libsf-common_files = ""
libsf-common_files += "${prefix}/lib/libsf_common.so"
libsf-common_files += "${prefix}/share/license/libsf-common"
MANIFESTFILES_${PN} = "libsf-common.manifest"

libsf-common-dev_files = ""
libsf-common-dev_files += "${prefix}/include/sf_common/*.h"
libsf-common-dev_files += "${prefix}/lib/pkgconfig/sf_common.pc"
MANIFESTFILES_${PN}-dev = "libsf-common.manifest"

FILES_${PN} = "${libsf-common_files}"
FILES_${PN}-dev = "${libsf-common-dev_files}"

PKG_libsf-common= "libsf-common"
PKG_libsf-common-dev= "libsf-common-dev"

require libsf-common-extraconf.inc

