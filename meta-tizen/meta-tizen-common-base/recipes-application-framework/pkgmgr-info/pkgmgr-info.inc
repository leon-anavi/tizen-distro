DESCRIPTION = "Packager Manager infomation api for package"
HOMEPAGE = "http://nohomepage.org"
SECTION = "Application Framework/Package Management"
LICENSE = "Apache-2.0"
PV = "0.0.134"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by pkgmgr-info-parser
PROVIDES += "pkgmgr-info-parser"


#PROVIDES by pkgmgr-info-parser-dev
PROVIDES += "pkgmgr-info-parser-dev"


#PROVIDES by pkgmgr-info


#PROVIDES by pkgmgr-info-dev
PROVIDES += "pkgmgr-info-dev"


RDEPENDS = ""
#RDEPENDS of pkgmgr-info-parser (${PN}-parser)
RDEPENDS_${PN}-parser += "pkgmgr-info"

#RDEPENDS of pkgmgr-info-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "pkgmgr-info"

#RDEPENDS of pkgmgr-info-parser-dev (${PN}-parser-dev)
RDEPENDS_${PN}-parser-dev += "tizen-platform-config"
RDEPENDS_${PN}-parser-dev += "pkgmgr-info"


DEPENDS = ""
#DEPENDS of pkgmgr-info
inherit tizen_cmake
DEPENDS += "libxml2"
DEPENDS += "dbus"
DEPENDS += "tizen-platform-config"
inherit pkgconfig
DEPENDS += "dlog"
DEPENDS += "smack"
DEPENDS += "dbus-glib"
DEPENDS += "sqlite3"
DEPENDS += "vconf"
DEPENDS += "libslp-db-util"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/pkgmgr-info.manifest .
 
 
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
 
 # create the directory for hosting Read-Write application manifest files
 mkdir -p ${D}${prefix}/share/packages
 
 
}

pkg_postinst_pkgmgr-info-parser() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postinst_${PN}() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
    chsmack -a '*' $D${prefix}/share/packages

}

pkg_postrm_${PN}() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_pkgmgr-info-parser() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " pkgmgr-info-parser "
PACKAGES += " pkgmgr-info "
PACKAGES += " pkgmgr-info-parser-dev "
PACKAGES += " pkgmgr-info-dev "

pkgmgr-info-parser_files = ""
pkgmgr-info-parser_files += "${prefix}/lib/libpkgmgr_parser.so.*"
pkgmgr-info-parser_files += "${sysconfdir}/package-manager/preload/preload_list.txt"
pkgmgr-info-parser_files += "${sysconfdir}/package-manager/preload/manifest.xsd"
pkgmgr-info-parser_files += "${sysconfdir}/package-manager/preload/xml.xsd"
pkgmgr-info-parser_files += "${sysconfdir}/package-manager/parser_path.conf"
pkgmgr-info-parser_files += "${sysconfdir}/package-manager/parserlib/metadata/mdparser_list.txt"
pkgmgr-info-parser_files += "${sysconfdir}/package-manager/parserlib/category/category_parser_list.txt"
pkgmgr-info-parser_files += "${sysconfdir}/package-manager/parserlib/tag_parser_list.txt"
CONFFILES_${PN}-parser = ""
CONFFILES_${PN}-parser += "${sysconfdir}/package-manager/preload/preload_list.txt"
CONFFILES_${PN}-parser += "${sysconfdir}/package-manager/preload/manifest.xsd"
CONFFILES_${PN}-parser += "${sysconfdir}/package-manager/preload/xml.xsd"
CONFFILES_${PN}-parser += "${sysconfdir}/package-manager/parser_path.conf"
CONFFILES_${PN}-parser += "${sysconfdir}/package-manager/parserlib/metadata/mdparser_list.txt"
CONFFILES_${PN}-parser += "${sysconfdir}/package-manager/parserlib/category/category_parser_list.txt"
CONFFILES_${PN}-parser += "${sysconfdir}/package-manager/parserlib/tag_parser_list.txt"
MANIFESTFILES_${PN}-parser = "pkgmgr-info.manifest"

pkgmgr-info_files = ""
pkgmgr-info_files += "${prefix}/lib/libpkgmgr-info.so.*"
pkgmgr-info_files += "%dir ${prefix}/share/packages"
MANIFESTFILES_${PN} = "pkgmgr-info.manifest"

pkgmgr-info-parser-dev_files = ""
pkgmgr-info-parser-dev_files += "${prefix}/include/pkgmgr/pkgmgr_parser.h"
pkgmgr-info-parser-dev_files += "${prefix}/include/pkgmgr/pkgmgr_parser_db.h"
pkgmgr-info-parser-dev_files += "${prefix}/lib/pkgconfig/pkgmgr-parser.pc"
pkgmgr-info-parser-dev_files += "${prefix}/lib/libpkgmgr_parser.so"
MANIFESTFILES_${PN}-parser-dev = "pkgmgr-info.manifest"

pkgmgr-info-dev_files = ""
pkgmgr-info-dev_files += "${prefix}/include/pkgmgr-info.h"
pkgmgr-info-dev_files += "${prefix}/lib/pkgconfig/pkgmgr-info.pc"
pkgmgr-info-dev_files += "${prefix}/lib/libpkgmgr-info.so"
MANIFESTFILES_${PN}-dev = "pkgmgr-info.manifest"

FILES_${PN}-parser = "${pkgmgr-info-parser_files}"
FILES_${PN} = "${pkgmgr-info_files}"
FILES_${PN}-parser-dev = "${pkgmgr-info-parser-dev_files}"
FILES_${PN}-dev = "${pkgmgr-info-dev_files}"

PKG_pkgmgr-info-parser= "pkgmgr-info-parser"
PKG_pkgmgr-info= "pkgmgr-info"
PKG_pkgmgr-info-parser-dev= "pkgmgr-info-parser-dev"
PKG_pkgmgr-info-dev= "pkgmgr-info-dev"

require pkgmgr-info-extraconf.inc

