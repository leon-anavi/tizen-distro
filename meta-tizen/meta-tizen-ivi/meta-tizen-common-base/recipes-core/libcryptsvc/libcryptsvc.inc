DESCRIPTION = "Crypto Service Library"
HOMEPAGE = "http://nohomepage.org"
SECTION = "Security/Libraries"
LICENSE = "Apache-2.0"
PV = "0.0.1"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by libcryptsvc-dev
PROVIDES += "libcryptsvc-dev"


#PROVIDES by libcryptsvc


RDEPENDS = ""
#RDEPENDS of libcryptsvc-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "libcryptsvc"


DEPENDS = ""
#DEPENDS of libcryptsvc
inherit tizen_cmake
inherit pkgconfig
DEPENDS += "dlog"
DEPENDS += "openssl"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/libcryptsvc.manifest .
 
 
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
 
 MAJORVER=`echo 0.0.1 | awk 'BEGIN {FS="."}{print $1}'`
 
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
         ${EXTRA_OECMAKE} . -DARCH=x86 -DFULLVER=0.0.1 -DMAJORVER=${MAJORVER} -DDESCRIPTION="Crypto Service Library (Development)"
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
}

pkg_postrm_${PN}() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " libcryptsvc-dev "
PACKAGES += " libcryptsvc "

libcryptsvc-dev_files = ""
libcryptsvc-dev_files += "${prefix}/include/*"
libcryptsvc-dev_files += "${prefix}/lib/pkgconfig/cryptsvc.pc"
MANIFESTFILES_${PN}-dev = "libcryptsvc.manifest"

libcryptsvc_files = ""
libcryptsvc_files += "${prefix}/lib/*.so*"
MANIFESTFILES_${PN} = "libcryptsvc.manifest"

FILES_${PN}-dev = "${libcryptsvc-dev_files}"
FILES_${PN} = "${libcryptsvc_files}"

PKG_libcryptsvc-dev= "libcryptsvc-dev"
PKG_libcryptsvc= "libcryptsvc"

require libcryptsvc-extraconf.inc

