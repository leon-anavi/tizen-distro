DESCRIPTION = "Badge library"
HOMEPAGE = "http://nohomepage.org"
SECTION = "Application Framework/Libraries"
LICENSE = "Apache-2.0"
PV = "0.0.5"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by badge-dev
PROVIDES += "badge-dev"


#PROVIDES by badge


#PROVIDES by badge-service-dev
PROVIDES += "badge-service-dev"


RDEPENDS = ""
#RDEPENDS of badge-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "badge"

#RDEPENDS of badge-service-dev (${PN}-service-dev)
RDEPENDS_${PN}-service-dev += "badge"


DEPENDS = ""
#DEPENDS of badge
inherit tizen_cmake
DEPENDS += "dbus"
DEPENDS += "tizen-platform-config"
inherit pkgconfig
DEPENDS += "dlog"
DEPENDS += "aul"
DEPENDS += "sqlite3"
DEPENDS += "libcom-core"
DEPENDS += "vconf"
DEPENDS += "dbus-glib"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/badge.manifest .
 
 
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
 install -D -m 0640 badge.sql ${D}${prefix}/share/badge/ressources/badge.sql
 install -D -m 0750 ${S}/packaging/init_db.sh ${D}${prefix}/share/badge/ressources/init_db.sh
 
 
}

pkg_postinst_badge() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_badge() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " badge-dev "
PACKAGES += " badge "
PACKAGES += " badge-service-dev "

badge-dev_files = ""
badge-dev_files += "${prefix}/include/badge/badge.h"
badge-dev_files += "${prefix}/include/badge/badge_error.h"
badge-dev_files += "${prefix}/include/badge/badge_setting.h"
badge-dev_files += "${prefix}/lib/libbadge.so"
badge-dev_files += "${prefix}/lib/pkgconfig/badge.pc"
MANIFESTFILES_${PN}-dev = "badge.manifest"

badge_files = ""
badge_files += "${prefix}/lib/libbadge.so.*"
badge_files += "${prefix}/share/badge"
badge_files += "${prefix}/share/badge/ressources/badge.sql"
badge_files += "${prefix}/share/badge/ressources/init_db.sh"
MANIFESTFILES_${PN} = "badge.manifest"

badge-service-dev_files = ""
badge-service-dev_files += "${prefix}/include/badge/service/badge_db.h"
badge-service-dev_files += "${prefix}/include/badge/service/badge_setting_service.h"
badge-service-dev_files += "${prefix}/lib/pkgconfig/badge-service.pc"
MANIFESTFILES_${PN}-service-dev = "badge.manifest"

FILES_${PN}-dev = "${badge-dev_files}"
FILES_${PN} = "${badge_files}"
FILES_${PN}-service-dev = "${badge-service-dev_files}"

PKG_badge-dev= "badge-dev"
PKG_badge= "badge"
PKG_badge-service-dev= "badge-service-dev"

require badge-extraconf.inc

