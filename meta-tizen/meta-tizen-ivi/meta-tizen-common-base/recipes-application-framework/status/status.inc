DESCRIPTION = "Status library"
HOMEPAGE = "http://nohomepage.org"
SECTION = "Applications/Core Applications"
LICENSE = "Apache-2.0"
PV = "0.0.1"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by status


#PROVIDES by status-dev
PROVIDES += "status-dev"


RDEPENDS = ""
#RDEPENDS of status (${PN})
RDEPENDS_${PN} += "glibc"

#RDEPENDS of status-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "status"


DEPENDS = ""
#DEPENDS of status
inherit tizen_cmake
DEPENDS += "dbus"
DEPENDS += "tizen-platform-config"
DEPENDS += "aul"
DEPENDS += "dlog"
inherit pkgconfig
DEPENDS += "vconf"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/status.manifest .
 
 
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
 
 export LDFLAGS="${LDFLAGS} -Wl,--rpath=${prefix}/lib -Wl,--as-needed"
 
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
 
 
   oe_runmake \
         DESTDIR=${D} \
         INSTALL_ROOT=${D} \
         BINDIR=${prefix}/bin \
   install  
   rm -f ${D}${infodir}/dir 
   find ${D} -regex ".*\.la$" | xargs rm -f -- 
   find ${D} -regex ".*\.a$" | xargs rm -f --
 mkdir -p ${D}${prefix}/share/license
 cp -f LICENSE ${D}${prefix}/share/license/status
 
 
 
}

pkg_postinst_${PN}() {
    #!/bin/sh -e

    users_gid=$(getent group users | cut -f3 -d':')
    init_vconf()
    {
        vconftool set -t int memory/private/libstatus/music/state 0 -i -g $users_gid
        vconftool set -t int memory/private/libstatus/radio/state 0 -i -g $users_gid
        vconftool set -t int memory/private/libstatus/vr/state 0 -i -g $users_gid
        vconftool set -t int memory/private/libstatus/music/pid -1 -i -g $users_gid
        vconftool set -t int memory/private/libstatus/radio/pid -1 -i -g $users_gid
        vconftool set -t int memory/private/libstatus/vr/pid -1 -i -g $users_gid
        vconftool set -t string memory/private/libstatus/message "" -i -g $users_gid
    }
    [ "x$D" == "x" ] && ldconfig
    init_vconf

}

pkg_postrm_${PN}() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " status "
PACKAGES += " status-dev "

status_files = ""
status_files += "${prefix}/lib/*.so*"
status_files += "${prefix}/share/license/status"
MANIFESTFILES_${PN} = "status.manifest"

status-dev_files = ""
status-dev_files += "${prefix}/include/status/*.h"
status-dev_files += "${prefix}/lib/pkgconfig/*.pc"
MANIFESTFILES_${PN}-dev = "status.manifest"

FILES_${PN} = "${status_files}"
FILES_${PN}-dev = "${status-dev_files}"

PKG_status= "status"
PKG_status-dev= "status-dev"

require status-extraconf.inc

