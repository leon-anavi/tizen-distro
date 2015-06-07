DESCRIPTION = "Bullet Continuous Collision Detection and Physics Library"
HOMEPAGE = "http://nohomepage.org"
SECTION = "System/Libraries"
LICENSE = "Zlib"
PV = "2.81"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by bullet-dev
PROVIDES += "bullet-dev"


#PROVIDES by libbullet
PROVIDES += "libbullet"


#PROVIDES by bullet


RDEPENDS = ""
#RDEPENDS of bullet-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "libbullet"


DEPENDS = ""
#DEPENDS of bullet
inherit tizen_cmake

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/bullet.manifest .
   
 
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
         ${EXTRA_OECMAKE} . -G "Unix Makefiles" -DBUILD_SHARED_LIBS=ON -DBUILD_EXTRAS=OFF -DBUILD_DEMOS=OFF -DBUILD_CPU_DEMOS=OFF -DUSE_GRAPHICAL_BENCHMARK=OFF -DCMAKE_INSTALL_PREFIX=/usr -DUSE_GLUT=OFF
 
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

pkg_postinst_libbullet() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_libbullet() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " bullet-dev "
PACKAGES += " libbullet "

bullet-dev_files = ""
bullet-dev_files += "${prefix}/include/*"
bullet-dev_files += "${prefix}/lib/*.so"
bullet-dev_files += "${prefix}/lib/pkgconfig/*"
MANIFESTFILES_${PN}-dev = "bullet.manifest"

libbullet_files = ""
libbullet_files += "${prefix}/lib/*.so.2.81"
libbullet_files += ""
MANIFESTFILES_lib${PN} = "bullet.manifest"

FILES_${PN}-dev = "${bullet-dev_files}"
FILES_lib${PN} = "${libbullet_files}"

PKG_bullet-dev= "bullet-dev"
PKG_libbullet= "libbullet"

require bullet-extraconf.inc

