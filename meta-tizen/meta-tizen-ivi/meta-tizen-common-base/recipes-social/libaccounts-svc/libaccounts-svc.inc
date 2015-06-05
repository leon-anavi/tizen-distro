DESCRIPTION = "Account DB library"
HOMEPAGE = "http://nohomepage.org"
SECTION = "Social & Content/Utilities"
LICENSE = "Apache-2.0"
PV = "0.2.52"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by libaccounts-svc


#PROVIDES by libaccounts-svc-dev
PROVIDES += "libaccounts-svc-dev"


RDEPENDS = ""
#RDEPENDS of libaccounts-svc (${PN})
RDEPENDS_${PN} += "sqlite3"
RDEPENDS_${PN} += "glibc"
RDEPENDS_${PN} += "libtzplatform-config"

#RDEPENDS of libaccounts-svc-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "libaccounts-svc"


DEPENDS = ""
#DEPENDS of libaccounts-svc
DEPENDS += "pkgmgr-info"
inherit tizen_cmake
DEPENDS += "libxml2"
DEPENDS += "tizen-platform-config"
DEPENDS += "capi-appfw-application"
inherit pkgconfig
DEPENDS += "dlog"
DEPENDS += "glib-2.0"
DEPENDS += "aul"
DEPENDS += "capi-base-common"
DEPENDS += "vconf"
DEPENDS += "libslp-db-util"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/libaccounts-svc.manifest ${S}/packaging/accounts_DB.sh .
 
 
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
 
 export CFLAGS="${CFLAGS} -fPIC -fvisibility=hidden"
 
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
 
 rm -rf ${D}
 
   oe_runmake \
         DESTDIR=${D} \
         INSTALL_ROOT=${D} \
         BINDIR=${prefix}/bin \
   install  
   rm -f ${D}${infodir}/dir 
   find ${D} -regex ".*\.la$" | xargs rm -f -- 
   find ${D} -regex ".*\.a$" | xargs rm -f --
 
 install -D -m 0750 ${S}/packaging/accounts_DB.sh ${D}${prefix}/share/libaccounts-svc/accounts_DB.sh
 
 rm -rf ${D}${prefix}/lib/accounts-svc
 
 
}

pkg_postinst_${PN}() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
    $D${prefix}/share/libaccounts-svc/accounts_DB.sh
    #set message key value to NULL
    vconftool set -t string db/account/msg '' -g 6514
    #smack labeling

}

pkg_postrm_${PN}() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " libaccounts-svc "
PACKAGES += " libaccounts-svc-dev "

libaccounts-svc_files = ""
libaccounts-svc_files += "${prefix}/lib/*.so.*"
libaccounts-svc_files += "${prefix}/bin/account-xml-verify"
libaccounts-svc_files += "${prefix}/share/libaccounts-svc/accounts_DB.sh"
MANIFESTFILES_${PN} = "libaccounts-svc.manifest"

libaccounts-svc-dev_files = ""
libaccounts-svc-dev_files += "${prefix}/lib/*.so"
libaccounts-svc-dev_files += "${prefix}/lib/pkgconfig/accounts-svc.pc"
libaccounts-svc-dev_files += "${prefix}/include/*.h"
libaccounts-svc-dev_files += "${prefix}/share/libaccounts-svc/accounts_DB.sh"
libaccounts-svc-dev_files += "${prefix}/bin/account-xml-verify"
MANIFESTFILES_${PN}-dev = "libaccounts-svc.manifest"

FILES_${PN} = "${libaccounts-svc_files}"
FILES_${PN}-dev = "${libaccounts-svc-dev_files}"

PKG_libaccounts-svc= "libaccounts-svc"
PKG_libaccounts-svc-dev= "libaccounts-svc-dev"

require libaccounts-svc-extraconf.inc

