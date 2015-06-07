DESCRIPTION = "Library to control privilege of application"
HOMEPAGE = "http://nohomepage.org"
SECTION = "Security/Access Control"
LICENSE = "Apache-2.0"
PV = "0.0.43.TIZEN"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by libprivilege-control


#PROVIDES by libprivilege-control-conf
PROVIDES += "libprivilege-control-conf"


#PROVIDES by libprivilege-control-dev
PROVIDES += "libprivilege-control-dev"


RDEPENDS = ""
#RDEPENDS of libprivilege-control (${PN})
RDEPENDS_${PN} += "sqlite3"
RDEPENDS_${PN} += "glibc"

#RDEPENDS of libprivilege-control-conf (${PN}-conf)
RDEPENDS_${PN}-conf += "libprivilege-control"

#RDEPENDS of libprivilege-control-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "libprivilege-control"


DEPENDS = ""
#DEPENDS of libprivilege-control
inherit tizen_cmake
DEPENDS += "tizen-platform-config"
inherit pkgconfig
DEPENDS += "dlog"
DEPENDS += "libiri"
DEPENDS += "smack"
DEPENDS += "sqlite3"
DEPENDS += "libcap"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/libprivilege-control.manifest .
 
 
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
 
 
 export CFLAGS="${CFLAGS} -Wno-implicit-function-declaration"
 
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
         ${EXTRA_OECMAKE} . -DCMAKE_BUILD_TYPE=RELEASE \
          -DCMAKE_VERBOSE_MAKEFILE=ON \
          -DTZ_SYS_DB=${prefix}/dbspace \
          -DTZ_SYS_HOME=/home \
          -DTZ_SYS_ETC=${sysconfdir} \
          -DSYSTEMD_UNIT_DIR=${systemd_unitdir}/system
 
 VERBOSE=1 oe_runmake ${PARALLEL_MAKE}
 
 
 
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
 mkdir -p ${D}${prefix}/share/privilege-control/
 mkdir -p ${D}${systemd_unitdir}/system/multi-user.target.wants
 ln -sf ${systemd_unitdir}/system/smack-rules.service ${D}${systemd_unitdir}/system/multi-user.target.wants/smack-rules.service
 mkdir -p ${D}${prefix}/dbspace
 sed -i 's|TZ_SYS_DB|${prefix}/dbspace|g' ${S}/packaging/libprivilege-control.manifest
 
 
}

pkg_postinst_${PN}() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
    $D${prefix}/share/privilege-control/db/updater.sh
    chsmack -a 'System' $D${prefix}/dbspace/.rules-db.db3*

}

pkg_postrm_${PN}() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " libprivilege-control "
PACKAGES += " libprivilege-control-conf "
PACKAGES += " libprivilege-control-dev "

libprivilege-control_files = ""
libprivilege-control_files += "${prefix}/lib/*.so.*"
libprivilege-control_files += "${prefix}/lib/librules-db-sql-udf.so"
libprivilege-control_files += "${systemd_unitdir}/system/smack-rules.service"
libprivilege-control_files += "${prefix}/bin/api_feature_loader"
libprivilege-control_files += "${systemd_unitdir}/system/multi-user.target.wants/smack-rules.service"
libprivilege-control_files += "${prefix}/share/privilege-control/db/rules-db.sql"
libprivilege-control_files += "${prefix}/share/privilege-control/db/rules-db-data.sql"
libprivilege-control_files += "${prefix}/share/privilege-control/db/updater.sh"
libprivilege-control_files += "${prefix}/share/privilege-control/db/updates/*"
libprivilege-control_files += "${prefix}/share/privilege-control/db/load-rules-db.sql"
libprivilege-control_files += "${sysconfdir}/opt/upgrade/220.libprivilege-updater.patch.sh"
libprivilege-control_files += "%dir ${prefix}/dbspace"
MANIFESTFILES_${PN} = "libprivilege-control.manifest"

libprivilege-control-conf_files = ""
libprivilege-control-conf_files += "${prefix}/dbspace/.privilege_control*.db"
MANIFESTFILES_${PN}-conf = "libprivilege-control.manifest"

libprivilege-control-dev_files = ""
libprivilege-control-dev_files += "${prefix}/include/*.h"
libprivilege-control-dev_files += "${prefix}/lib/*.so"
libprivilege-control-dev_files += "${prefix}/lib/pkgconfig/*.pc"
MANIFESTFILES_${PN}-dev = "libprivilege-control.manifest"

FILES_${PN} = "${libprivilege-control_files}"
FILES_${PN}-conf = "${libprivilege-control-conf_files}"
FILES_${PN}-dev = "${libprivilege-control-dev_files}"

PKG_libprivilege-control= "libprivilege-control"
PKG_libprivilege-control-conf= "libprivilege-control-conf"
PKG_libprivilege-control-dev= "libprivilege-control-dev"

require libprivilege-control-extraconf.inc

