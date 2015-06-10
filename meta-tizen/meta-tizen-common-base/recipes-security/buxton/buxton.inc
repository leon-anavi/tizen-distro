DESCRIPTION = "A security-enabled configuration system"
HOMEPAGE = "https://github.com/sofar/buxton"
SECTION = "System/Configuration"
LICENSE = "LGPL-2.1+"
PV = "5"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by buxton-dev
PROVIDES += "buxton-dev"


#PROVIDES by buxtonsimple
PROVIDES += "buxtonsimple"


#PROVIDES by buxton-docs
PROVIDES += "buxton-docs "


#PROVIDES by buxtonsimple-dev
PROVIDES += "buxtonsimple-dev"


#PROVIDES by buxton


RDEPENDS = ""
#RDEPENDS of buxton-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "buxton"

#RDEPENDS of buxtonsimple (${PN}simple)
RDEPENDS_${PN}simple += "buxton"

#RDEPENDS of buxtonsimple-dev (${PN}simple-dev)
RDEPENDS_${PN}simple-dev += "buxton"

#RDEPENDS of buxton (${PN})
RDEPENDS_${PN} += "coreutils"
RDEPENDS_${PN} += "smack"
RDEPENDS_${PN} += "buxton"


DEPENDS = ""
#DEPENDS of buxton
inherit pkgconfig
DEPENDS += "libcheck"
DEPENDS += "systemd"
DEPENDS += "attr"
DEPENDS += "gdbm"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/buxton.manifest .
 
 
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
  
  
  autotools_do_configure
  make ${PARALLEL_MAKE}
  
  
  
}
EXTRA_OECONF += ""

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
 # TODO: need to define needed layers for Tizen in tizen.conf
 install -m 0644 ${S}/packaging/tizen.conf ${D}${sysconfdir}/buxton.conf
 
 
}

pkg_postinst_${PN}() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
    #buxtond runs as user buxton, which much be created
    useradd buxton
    buxtonctl create-db base
    buxtonctl create-db isp
    if [ "$1" -eq 1 ] ; then
        # The initial DBs will not have the correct labels and
        # permissions when created in postinstall during image
        # creation, so we set these file attributes here.
        chsmack -a System ${localstatedir}/lib/buxton/*.db
        chown buxton:buxton ${localstatedir}/lib/buxton/*.db
    fi

}

pkg_postrm_${PN}() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " buxton-dev "
PACKAGES += " buxtonsimple "
PACKAGES += " buxton-docs "
PACKAGES += " buxtonsimple-dev "
PACKAGES += " buxton "

buxton-dev_files = ""
buxton-dev_files += "${prefix}/include/buxton.h"
buxton-dev_files += "${prefix}/lib/libbuxton.so"
buxton-dev_files += "${prefix}/lib/pkgconfig/buxton.pc"
MANIFESTFILES_${PN}-dev = "buxton.manifest"

buxtonsimple_files = ""
buxtonsimple_files += "${prefix}/lib/libbuxtonsimple.so.*"
MANIFESTFILES_${PN}simple = "buxton.manifest"

buxton-docs_files = ""

buxtonsimple-dev_files = ""
buxtonsimple-dev_files += "${prefix}/include/buxtonsimple.h"
buxtonsimple-dev_files += "${prefix}/lib/libbuxtonsimple.so"
buxtonsimple-dev_files += "${prefix}/lib/pkgconfig/buxtonsimple.pc"
MANIFESTFILES_${PN}simple-dev = "buxton.manifest"

buxton_files = ""
buxton_files += "${sysconfdir}/buxton.conf"
buxton_files += "${prefix}/bin/buxtonctl"
buxton_files += "${prefix}/lib/buxton/*.so"
buxton_files += "${prefix}/lib/libbuxton.so.*"
buxton_files += "${prefix}/lib/systemd/system/buxton.service"
buxton_files += "${prefix}/lib/systemd/system/buxton.socket"
buxton_files += "${prefix}/lib/systemd/system/sockets.target.wants/buxton.socket"
buxton_files += "${prefix}/sbin/buxtond"
buxton_files += "%dir ${localstatedir}/lib/buxton"
MANIFESTFILES_${PN} = "buxton.manifest"

FILES_${PN}-dev = "${buxton-dev_files}"
FILES_${PN}simple = "${buxtonsimple_files}"
FILES_${PN}-docs = "${buxton-docs_files}"
FILES_${PN}simple-dev = "${buxtonsimple-dev_files}"
FILES_${PN} = "${buxton_files}"

PKG_buxton-dev= "buxton-dev"
PKG_buxtonsimple= "buxtonsimple"
PKG_buxton-docs= "buxton-docs"
PKG_buxtonsimple-dev= "buxtonsimple-dev"
PKG_buxton= "buxton"

require buxton-extraconf.inc

