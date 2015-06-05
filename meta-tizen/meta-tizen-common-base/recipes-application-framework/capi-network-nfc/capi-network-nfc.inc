DESCRIPTION = "NFC Core API"
HOMEPAGE = "http://nohomepage.org"
SECTION = "Network & Connectivity/NFC"
LICENSE = "Apache-2.0"
PV = "0.1.5"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by capi-network-nfc


#PROVIDES by capi-network-nfc-dev
PROVIDES += "capi-network-nfc-dev"


RDEPENDS = ""
#RDEPENDS of capi-network-nfc (${PN})
RDEPENDS_${PN} += "glibc"

#RDEPENDS of capi-network-nfc-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "capi-network-nfc"


DEPENDS = ""
#DEPENDS of capi-network-nfc
inherit tizen_cmake
inherit pkgconfig
DEPENDS += "dlog"
DEPENDS += "glib-2.0"
DEPENDS += "vconf"
DEPENDS += "capi-base-common"
DEPENDS += "nfc-manager-neard"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/capi-network-nfc.manifest .
 
 
 
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
 
 MAJORVER=`echo 0.1.5 | awk 'BEGIN {FS="."}{print $1}'`
 
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
         ${EXTRA_OECMAKE} . -DFULLVER=0.1.5 -DMAJORVER=${MAJORVER} \
          -DX11_SUPPORT=Off
 
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
PACKAGES += " capi-network-nfc "
PACKAGES += " capi-network-nfc-dev "

capi-network-nfc_files = ""
capi-network-nfc_files += "${prefix}/lib/libcapi-network-nfc.so.*"
MANIFESTFILES_${PN} = "capi-network-nfc.manifest"

capi-network-nfc-dev_files = ""
capi-network-nfc-dev_files += "${prefix}/include/network/*.h"
capi-network-nfc-dev_files += "${prefix}/lib/pkgconfig/*.pc"
capi-network-nfc-dev_files += "${prefix}/lib/libcapi-network-nfc.so"
MANIFESTFILES_${PN}-dev = "capi-network-nfc.manifest"

FILES_${PN} = "${capi-network-nfc_files}"
FILES_${PN}-dev = "${capi-network-nfc-dev_files}"

PKG_capi-network-nfc= "capi-network-nfc"
PKG_capi-network-nfc-dev= "capi-network-nfc-dev"

require capi-network-nfc-extraconf.inc

