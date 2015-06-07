DESCRIPTION = "Telephony dbus client library"
HOMEPAGE = "http://nohomepage.org"
SECTION = "Telephony/Libraries"
LICENSE = "Apache-2.0"
PV = "0.6.71"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by libtapi-dev
PROVIDES += "libtapi-dev"


#PROVIDES by libtapi
# the PROVIDES rules is ignore "libslp-tapi  "
PROVIDES += "libslp-tapi"
RPROVIDES_libtapi += "libslp-tapi"


RDEPENDS = ""
#RDEPENDS of libtapi-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "libtapi"


DEPENDS = ""
#DEPENDS of libtapi
DEPENDS += "libtapi3"
inherit tizen_cmake
DEPENDS += "security-server"
DEPENDS += "dlog"
inherit pkgconfig
DEPENDS += "glib-2.0"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/libtapi.manifest .
 
 
 
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
 
 rm -rf ${D}
 
   oe_runmake \
         DESTDIR=${D} \
         INSTALL_ROOT=${D} \
         BINDIR=${prefix}/bin \
   install  
   rm -f ${D}${infodir}/dir 
   find ${D} -regex ".*\.la$" | xargs rm -f -- 
   find ${D} -regex ".*\.a$" | xargs rm -f --
 
 rm -rf ${D}/usr/include/telephony/tapi/.gitignore
 
 
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
PACKAGES += " libtapi-dev "
PACKAGES += " libtapi "

libtapi-dev_files = ""
libtapi-dev_files += "${prefix}/include/telephony-client/*.h"
libtapi-dev_files += "${prefix}/lib/pkgconfig/*.pc"
libtapi-dev_files += "${prefix}/lib/*.so"
MANIFESTFILES_${PN}-dev = "libtapi.manifest"

libtapi_files = ""
libtapi_files += "${prefix}/lib/*.so.*"
libtapi_files += "${prefix}/bin/tapitest-legacy"
MANIFESTFILES_${PN} = "libtapi.manifest"

FILES_${PN}-dev = "${libtapi-dev_files}"
FILES_${PN} = "${libtapi_files}"

PKG_libtapi-dev= "libtapi-dev"
PKG_libtapi= "libtapi"

require libtapi-extraconf.inc

