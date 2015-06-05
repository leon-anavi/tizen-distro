DESCRIPTION = "Secure storage"
HOMEPAGE = "http://nohomepage.org"
SECTION = "System/Security"
LICENSE = "Apache 2.0"
PV = "0.12.9"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by secure-storage


#PROVIDES by ss-server
PROVIDES += "ss-server"


#PROVIDES by libss-client-dev
PROVIDES += "libss-client-dev"


#PROVIDES by libss-client
PROVIDES += "libss-client"
# the PROVIDES rules is ignore "libss-client.so  "
PROVIDES += "libss-client.so"
RPROVIDES_libss-client += "libss-client.so"


RDEPENDS = ""
#RDEPENDS of libss-client (libss-client)
RDEPENDS_libss-client += "dukgenerator"

#RDEPENDS of ss-server (ss-server)
RDEPENDS_ss-server += "libss-client"
RDEPENDS_ss-server += "systemd"

#RDEPENDS of libss-client-dev (libss-client-dev)
RDEPENDS_libss-client-dev += "libss-client"


DEPENDS = ""
#DEPENDS of secure-storage
DEPENDS += "systemd"
DEPENDS += "openssl"
inherit tizen_cmake
DEPENDS += "security-server"
DEPENDS += "dlog"
inherit pkgconfig
DEPENDS += "dukgenerator"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/libss-client.manifest ${S}/packaging/libss-client-devel.manifest ${S}/packaging/ss-server.manifest .
 
 
 
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
 
 mkdir -p ${D}${prefix}/lib/systemd/system/multi-user.target.wants
 mkdir -p ${D}${prefix}/lib/systemd/system/sockets.target.wants
 ln -s ../secure-storage.service ${D}${prefix}/lib/systemd/system/multi-user.target.wants/secure-storage.service
 ln -s ../secure-storage.socket ${D}${prefix}/lib/systemd/system/sockets.target.wants/secure-storage.socket
 
 mkdir -p ${D}/usr/share/license
 cp LICENSE.APLv2 ${D}/usr/share/license/ss-server
 cp LICENSE.APLv2 ${D}/usr/share/license/libss-client
 
 
}

pkg_postinst_libss-client() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postinst_ss-server() {
    #!/bin/sh -e

    systemctl daemon-reload
    if [ $1 == 1 ]; then
        systemctl enable secure-storage.service -q
        systemctl restart secure-storage.service
    fi

}

pkg_prerm_ss-server() {
    #!/bin/sh -e

    if [ $1 == 0 ]; then
        systemctl stop secure-storage.service
        systemctl disable secure-storage.service -q
    fi

}

pkg_postrm_libss-client() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_ss-server() {
    #!/bin/sh -e

    systemctl daemon-reload

}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " libss-client "
PACKAGES += " ss-server "
PACKAGES += " libss-client-dev "

libss-client_files = ""
libss-client_files += "${prefix}/lib/libss-client.so.*"
libss-client_files += "/usr/share/license/libss-client"
MANIFESTFILES_libss-client = "libss-client.manifest"

ss-server_files = ""
ss-server_files += "${prefix}/bin/ss-server"
ss-server_files += "${prefix}/lib/systemd/system/secure-storage.service"
ss-server_files += "${prefix}/lib/systemd/system/multi-user.target.wants/secure-storage.service"
ss-server_files += "${prefix}/lib/systemd/system/secure-storage.socket"
ss-server_files += "${prefix}/lib/systemd/system/sockets.target.wants/secure-storage.socket"
ss-server_files += "${prefix}/share/secure-storage/config"
ss-server_files += "/usr/share/license/ss-server"
MANIFESTFILES_ss-server = "ss-server.manifest"

libss-client-dev_files = ""
libss-client-dev_files += "${prefix}/include/ss_manager.h"
libss-client-dev_files += "${prefix}/lib/pkgconfig/secure-storage.pc"
libss-client-dev_files += "${prefix}/lib/libss-client.so"
MANIFESTFILES_libss-client-dev = "libss-client-devel.manifest"

FILES_libss-client = "${libss-client_files}"
FILES_ss-server = "${ss-server_files}"
FILES_libss-client-dev = "${libss-client-dev_files}"

PKG_libss-client= "libss-client"
PKG_ss-server= "ss-server"
PKG_libss-client-dev= "libss-client-dev"

require secure-storage-extraconf.inc

