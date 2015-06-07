DESCRIPTION = "Device Unique Key Library"
HOMEPAGE = "http://nohomepage.org"
SECTION = "Security/Libraries"
LICENSE = "Apache-2.0"
PV = "1.0.0"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by dukgenerator-dev
PROVIDES += "dukgenerator-dev"


#PROVIDES by dukgenerator


RDEPENDS = ""
#RDEPENDS of dukgenerator-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "dukgenerator"


DEPENDS = ""
#DEPENDS of dukgenerator
DEPENDS += "libcryptsvc"
inherit tizen_cmake
inherit pkgconfig
DEPENDS += "openssl"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/dukgenerator.manifest .
 
 
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
 
 MAJORVER=`echo 1.0.0 | awk 'BEGIN {FS="."}{print $1}'`
 
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
         ${EXTRA_OECMAKE} . -DLIB_INSTALL_DIR:PATH=${prefix}/lib -DFULLVER=1.0.0 -DMAJORVER=${MAJORVER} -DDESCRIPTION="Device Unique Key Library" -DBUILD_SHARED_LIBS:BOOL=OFF
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
 
 make DESTDIR=${D} INSTALL_ROOT=${D} install
 rm -f ${D}${infodir}/dir
 find ${D} -regex ".*\\.la$" | xargs rm -f --
 
 
}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " dukgenerator-dev "
PACKAGES += " dukgenerator "

dukgenerator-dev_files = ""
dukgenerator-dev_files += "${prefix}/include/*"
dukgenerator-dev_files += "${prefix}/lib/pkgconfig/dukgenerator.pc"
MANIFESTFILES_${PN}-dev = "dukgenerator.manifest"

dukgenerator_files = ""
dukgenerator_files += "${prefix}/lib/*.a"
MANIFESTFILES_${PN} = "dukgenerator.manifest"

FILES_${PN}-dev = "${dukgenerator-dev_files}"
FILES_${PN} = "${dukgenerator_files}"

PKG_dukgenerator-dev= "dukgenerator-dev"
PKG_dukgenerator= "dukgenerator"

require dukgenerator-extraconf.inc

