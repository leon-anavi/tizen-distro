DESCRIPTION = "Linux Key Management Utilities"
HOMEPAGE = "http://people.redhat.com/~dhowells/keyutils/"
SECTION = "System/Kernel"
LICENSE = "GPL-2.0+ and LGPL-2.1+"
PV = "1.5.3"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by keyutils


#PROVIDES by libkeyutils
PROVIDES += "libkeyutils"


#PROVIDES by keyutils-dev
PROVIDES += "keyutils-dev"


RDEPENDS = ""
#RDEPENDS of keyutils-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "libkeyutils"
RDEPENDS_${PN}-dev += "glibc"


DEPENDS = ""

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/keyutils.manifest .
 
 
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
 
 oe_runmake ${PARALLEL_MAKE} NO_ARLIB=1 CFLAGS="$RPM_OPT_FLAGS" CC="${CC}"
 
 
 
}

do_install() {
 export RPM_BUILD_ROOT=${D}
 cd ${S}
 LANG=C
 export LANG
 unset DISPLAY
 rm -rf ${D}
 mkdir -p ${D}
 
 oe_runmake install \
         NO_ARLIB=1 \
         DESTDIR=${D} \
         LIBDIR=${prefix}/lib \
         USRLIBDIR=${prefix}/lib \
         BINDIR=${prefix}/bin \
         SBINDIR=${prefix}/sbin
 
 
}

pkg_postinst_libkeyutils() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_libkeyutils() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " keyutils "
PACKAGES += " libkeyutils "
PACKAGES += " keyutils-dev "

keyutils_files = ""
keyutils_files += "${prefix}/sbin/*"
keyutils_files += "${prefix}/bin/*"
keyutils_files += "${prefix}/share/keyutils"
keyutils_files += "${mandir}/*/*"
keyutils_files += "/etc/*"
MANIFESTFILES_${PN} = "keyutils.manifest"

libkeyutils_files = ""
libkeyutils_files += "${prefix}/lib/libkeyutils.so.*"
MANIFESTFILES_lib${PN} = "keyutils.manifest"

keyutils-dev_files = ""
keyutils-dev_files += "${prefix}/lib/libkeyutils.so"
keyutils-dev_files += "${prefix}/include/*"
MANIFESTFILES_${PN}-dev = "keyutils.manifest"

FILES_${PN} = "${keyutils_files}"
FILES_lib${PN} = "${libkeyutils_files}"
FILES_${PN}-dev = "${keyutils-dev_files}"

PKG_keyutils= "keyutils"
PKG_libkeyutils= "libkeyutils"
PKG_keyutils-dev= "keyutils-dev"

require keyutils-extraconf.inc

