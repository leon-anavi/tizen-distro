DESCRIPTION = "Contacts Service"
HOMEPAGE = "http://nohomepage.org"
SECTION = "Social & Contents/Pim"
LICENSE = "Apache-2.0"
PV = "0.10.3"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by contacts-service2
PROVIDES += "contacts-service2"


#PROVIDES by contacts-service


#PROVIDES by contacts-service2-dev
PROVIDES += "contacts-service2-dev"


RDEPENDS = ""
#RDEPENDS of contacts-service2 (${PN}2)
RDEPENDS_${PN}2 += "libprivilege-control"

#RDEPENDS of contacts-service (${PN})
RDEPENDS_${PN} += "sqlite3"
RDEPENDS_${PN} += "coreutils"
RDEPENDS_${PN} += "glibc"
RDEPENDS_${PN} += "vconf"

#RDEPENDS of contacts-service2-dev (${PN}2-dev)
RDEPENDS_${PN}2-dev += "contacts-service2"


DEPENDS = ""
#DEPENDS of contacts-service
DEPENDS += "pims-ipc"
DEPENDS += "libaccounts-svc"
inherit tizen_cmake
DEPENDS += "capi-media-image-util"
DEPENDS += "tizen-platform-config"
inherit pkgconfig
DEPENDS += "dlog"
DEPENDS += "glib-2.0"
DEPENDS += "libexif"
DEPENDS += "smack"
DEPENDS += "libtapi"
DEPENDS += "security-server"
DEPENDS += "sqlite3"
DEPENDS += "capi-base-common"
DEPENDS += "badge"
DEPENDS += "vconf"
DEPENDS += "libslp-db-util"
DEPENDS += "icu"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/contacts-service2.manifest .
 
 
 
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
         ${EXTRA_OECMAKE} . -DTZ_SYS_ETC=${sysconfdir}
 oe_runmake ${PARALLEL_MAKE}
 
 
 
 
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
 
 mkdir -p ${D}${prefix}/lib/systemd/user/tizen-middleware.target.wants
 install -m 0644 ${S}/packaging/contacts-service.service ${D}${prefix}/lib/systemd/user/contacts-service.service
 ln -s ../contacts-service.service ${D}${prefix}/lib/systemd/user/tizen-middleware.target.wants/contacts-service.service
 
 mkdir -p ${D}${prefix}/lib/systemd/user/sockets.target.wants
 install -m 0644 ${S}/packaging/contacts-service.socket ${D}${prefix}/lib/systemd/user/contacts-service.socket
 ln -s ../contacts-service.socket ${D}${prefix}/lib/systemd/user/sockets.target.wants/contacts-service.socket
 
 
 
}

pkg_postinst_contacts-service2() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
    vconftool set -t int file/private/contacts-service/default_lang 0 -g 6005 -s contacts-service::vconf-private
    vconftool set -t int db/contacts-svc/name_sorting_order 0 -g 6005 -s contacts-service::vconf
    vconftool set -t int db/contacts-svc/name_display_order 0 -g 6005 -s contacts-service::vconf
    vconftool set -t int db/contacts-svc/phonenumber_min_match_digit 8 -g 6005 -s contacts-service::vconf

}

pkg_postrm_contacts-service2() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_${PN}() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " contacts-service2 "
PACKAGES += " contacts-service2-dev "

contacts-service2_files = ""
contacts-service2_files += "${prefix}/lib/libcontacts-service2.so.*"
contacts-service2_files += "${prefix}/bin/contacts-service-ipcd*"
contacts-service2_files += "${prefix}/lib/systemd/user/contacts-service.service"
contacts-service2_files += "${prefix}/lib/systemd/user/tizen-middleware.target.wants/contacts-service.service"
contacts-service2_files += "${prefix}/lib/systemd/user/sockets.target.wants/contacts-service.socket"
contacts-service2_files += "${prefix}/lib/systemd/user/contacts-service.socket"
MANIFESTFILES_${PN}2 = "contacts-service2.manifest"

contacts-service2-dev_files = ""
contacts-service2-dev_files += "${prefix}/lib/libcontacts-service2.so"
contacts-service2-dev_files += "${prefix}/lib/pkgconfig/contacts-service2.pc"
contacts-service2-dev_files += "${prefix}/include/contacts-svc/contacts.h"
contacts-service2-dev_files += "${prefix}/include/contacts-svc/contacts_*.h"

FILES_${PN}2 = "${contacts-service2_files}"
FILES_${PN}2-dev = "${contacts-service2-dev_files}"

PKG_contacts-service2= "contacts-service2"
PKG_contacts-service2-dev= "contacts-service2-dev"

require contacts-service-extraconf.inc

