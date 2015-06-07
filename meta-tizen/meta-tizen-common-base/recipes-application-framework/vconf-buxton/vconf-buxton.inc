DESCRIPTION = "Configuration system library"
HOMEPAGE = "http://nohomepage.org"
SECTION = "System/Libraries"
LICENSE = "Apache-2.0"
PV = "0.3"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by vconf-buxton-dev
PROVIDES += "vconf-buxton-dev"
# the PROVIDES rules is ignore "vconf-dev  "
PROVIDES += "vconf-dev"
RPROVIDES_vconf-buxton-dev += "vconf-dev"


#PROVIDES by vconf-buxton-keys-dev
PROVIDES += "vconf-buxton-keys-dev"
# the PROVIDES rules is ignore "vconf-keys-dev  "
PROVIDES += "vconf-keys-dev"
RPROVIDES_vconf-buxton-keys-dev += "vconf-keys-dev"


#PROVIDES by vconf-buxton
# the PROVIDES rules is ignore "vconf  "
PROVIDES += "vconf"
RPROVIDES_vconf-buxton += "vconf"


RDEPENDS = ""
#RDEPENDS of vconf-buxton-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "vconf-buxton-keys-dev"
RDEPENDS_${PN}-dev += "vconf-buxton"

#RDEPENDS of vconf-buxton-keys-dev (${PN}-keys-dev)
RDEPENDS_${PN}-keys-dev += "vconf-buxton"
RDEPENDS_${PN}-keys-dev += "vconf-internal-keys-dev"

#RDEPENDS of vconf-buxton (${PN})
RDEPENDS_${PN} += "glibc"
RDEPENDS_${PN} += "util-linux"


DEPENDS = ""
#DEPENDS of vconf-buxton
DEPENDS += "vconf-internal-keys"
DEPENDS += "buxton"
inherit tizen_cmake
inherit pkgconfig
DEPENDS += "glib-2.0"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q -n vconf-buxton-0.3
 cp ${S}/packaging/vconf-buxton.manifest .
 
 
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
         ${EXTRA_OECMAKE} -DLIBNAME:STRING=vconf -DTOOLNAME:STRING=vconftool .
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
 mv ${D}${systemd_unitdir}/system/vconf-buxton-setup.service ${D}${systemd_unitdir}/system/vconf-setup.service
 mkdir -p ${D}${systemd_unitdir}/system/basic.target.wants
 ln -sf ../vconf-setup.service ${D}${systemd_unitdir}/system/basic.target.wants/
 
 
}

pkg_postinst_${PN}() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
    vconf-buxton-init-from-vconf.sh

}

pkg_postrm_${PN}() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig

}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " vconf-buxton-dev "
PACKAGES += " vconf-buxton-keys-dev "
PACKAGES += " vconf-buxton "

vconf-buxton-dev_files = ""
vconf-buxton-dev_files += "${prefix}/include/vconf/vconf.h"
vconf-buxton-dev_files += "${prefix}/include/vconf/vconf-buxton.h"
vconf-buxton-dev_files += "${prefix}/lib/pkgconfig/vconf.pc"
vconf-buxton-dev_files += "${prefix}/lib/libvconf.so"
MANIFESTFILES_${PN}-dev = "vconf-buxton.manifest"

vconf-buxton-keys-dev_files = ""
vconf-buxton-keys-dev_files += "${prefix}/include/vconf/vconf-keys.h"
vconf-buxton-keys-dev_files += "${prefix}/include/vconf/vconf-buxton-keys.h"
MANIFESTFILES_${PN}-keys-dev = "vconf-buxton.manifest"

vconf-buxton_files = ""
vconf-buxton_files += "${prefix}/bin/vconftool"
vconf-buxton_files += "${prefix}/bin/vconf-buxton-init-from-vconf.sh"
vconf-buxton_files += "${prefix}/bin/vconf-buxton-restore-mem-layer.sh"
vconf-buxton_files += "${prefix}/bin/vconf-buxton-backup-mem-layer.sh"
vconf-buxton_files += "${prefix}/lib/libvconf.so.*"
vconf-buxton_files += "${systemd_unitdir}/system/basic.target.wants/vconf-setup.service"
vconf-buxton_files += "${systemd_unitdir}/system/vconf-setup.service"
MANIFESTFILES_${PN} = "vconf-buxton.manifest"

FILES_${PN}-dev = "${vconf-buxton-dev_files}"
FILES_${PN}-keys-dev = "${vconf-buxton-keys-dev_files}"
FILES_${PN} = "${vconf-buxton_files}"

PKG_vconf-buxton-dev= "vconf-buxton-dev"
PKG_vconf-buxton-keys-dev= "vconf-buxton-keys-dev"
PKG_vconf-buxton= "vconf-buxton"

require vconf-buxton-extraconf.inc

