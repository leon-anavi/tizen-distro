DESCRIPTION = "Internet bookmark and history API"
HOMEPAGE = "http://nohomepage.org"
SECTION = "Web Framework/API"
LICENSE = "Apache-2.0"
PV = "0.0.15"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by capi-web-favorites


#PROVIDES by capi-web-favorites-dev
PROVIDES += "capi-web-favorites-dev"


RDEPENDS = ""
#RDEPENDS of capi-web-favorites (${PN})
RDEPENDS_${PN} += "glibc"

#RDEPENDS of capi-web-favorites-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "capi-web-favorites"


DEPENDS = ""
#DEPENDS of capi-web-favorites
inherit tizen_cmake
DEPENDS += "evas"
DEPENDS += "tizen-platform-config"
inherit pkgconfig
DEPENDS += "dlog"
DEPENDS += "capi-base-common"
DEPENDS += "libslp-db-util"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/capi-web-favorites.manifest .
 
 
 
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
         ${EXTRA_OECMAKE} . -DTZ_SYS_SHARE=${prefix}/share
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
    source /etc/tizen-platform.conf
    users_gid=$(getent group $TZ_SYS_USER_GROUP | cut -f3 -d':')
    chsmack -a 'User' /opt/usr/dbspace/.browser-history.db*
    chsmack -a 'User' /opt/usr/dbspace/.internet_bookmark.db*
    # set default vconf values
    ##################################################
    #internal keys
    vconftool set -t string db/browser/browser_user_agent "System user agent" -g $users_gid -f
    vconftool set -t string db/browser/custom_user_agent "" -g $users_gid -f
    #public keys
    vconftool set -t string db/browser/user_agent "Mozilla/5.0 (Linux; Tizen 2.1; sdk) AppleWebKit/537.3 (KHTML, like Gecko) Version/2.1 Mobile Safari/537.3" -g $users_gid -f

}

pkg_postrm_${PN}() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " capi-web-favorites "
PACKAGES += " capi-web-favorites-dev "

capi-web-favorites_files = ""
capi-web-favorites_files += "${prefix}/lib/libcapi-web-favorites.so"
capi-web-favorites_files += "${prefix}/share/capi-web-favorites/internet_bookmark_DB_init.sh"
capi-web-favorites_files += "${prefix}/share/capi-web-favorites/browser_history_DB_init.sh"
MANIFESTFILES_${PN} = "capi-web-favorites.manifest"

capi-web-favorites-dev_files = ""
capi-web-favorites-dev_files += "${prefix}/include/web/*.h"
capi-web-favorites-dev_files += "${prefix}/lib/pkgconfig/*.pc"
MANIFESTFILES_${PN}-dev = "capi-web-favorites.manifest"

FILES_${PN} = "${capi-web-favorites_files}"
FILES_${PN}-dev = "${capi-web-favorites-dev_files}"

PKG_capi-web-favorites= "capi-web-favorites"
PKG_capi-web-favorites-dev= "capi-web-favorites-dev"

require capi-web-favorites-extraconf.inc

