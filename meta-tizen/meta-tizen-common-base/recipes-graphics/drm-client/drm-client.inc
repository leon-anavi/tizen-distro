DESCRIPTION = "DRM client Package"
HOMEPAGE = "http://nohomepage.org"
SECTION = "Security/Libraries"
LICENSE = "Apache-2.0"
PV = "0.0.30"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by drm-client-dev
PROVIDES += "drm-client-dev"


#PROVIDES by drm-client


RDEPENDS = ""
#RDEPENDS of drm-client-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "drm-client"


DEPENDS = ""
#DEPENDS of drm-client
DEPENDS += "glib-2.0"
inherit tizen_cmake
inherit pkgconfig
DEPENDS += "dlog"
DEPENDS += "capi-base-common"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/drm-client.manifest .
 
 
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
PACKAGES += " drm-client-dev "
PACKAGES += " drm-client "

drm-client-dev_files = ""
drm-client-dev_files += "${prefix}/include/drm-client/*"
drm-client-dev_files += "${prefix}/lib/*.so"
drm-client-dev_files += "${prefix}/lib/pkgconfig/drm-client.pc"
MANIFESTFILES_${PN}-dev = "drm-client.manifest"

drm-client_files = ""
drm-client_files += "${prefix}/lib/*.so.*"
MANIFESTFILES_${PN} = "drm-client.manifest"

FILES_${PN}-dev = "${drm-client-dev_files}"
FILES_${PN} = "${drm-client_files}"

PKG_drm-client-dev= "drm-client-dev"
PKG_drm-client= "drm-client"

require drm-client-extraconf.inc

