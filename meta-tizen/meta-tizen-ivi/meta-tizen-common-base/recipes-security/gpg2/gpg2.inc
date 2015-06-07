DESCRIPTION = "GnuPG 2"
HOMEPAGE = "http://www.gnupg.org/aegypten2/"
SECTION = "Security/Certificate Management"
LICENSE = "GPL-3.0+"
PV = "2.0.19"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by gpg2
# the PROVIDES rules is ignore "gnupg = 2.0.19"
PROVIDES += "gnupg"
RPROVIDES_gpg2 += "gnupg"
# the PROVIDES rules is ignore "gpg = 1.4.9"
PROVIDES += "gpg"
RPROVIDES_gpg2 += "gpg"
# the PROVIDES rules is ignore "newpg  "
PROVIDES += "newpg"
RPROVIDES_gpg2 += "newpg"
# the PROVIDES rules is ignore "gpg2_signd_support  "
PROVIDES += "gpg2_signd_support"
RPROVIDES_gpg2 += "gpg2_signd_support"


RDEPENDS = ""

DEPENDS = ""
#DEPENDS of gpg2
#Replace "DEPENDS" on gettext by "inherit gettext"
inherit gettext
DEPENDS += "libksba"
DEPENDS += "libassuan"
DEPENDS += "adns"
DEPENDS += "pth"
DEPENDS += "zlib"
inherit pkgconfig
DEPENDS += "libgpg-error"
DEPENDS_append_class-native = " automake-native"
DEPENDS_append_class-target = " automake-native"
DEPENDS_append_class-native = " readline-native"
DEPENDS_append_class-target = " readline-native"
DEPENDS += "libusb"
DEPENDS += "expect"
DEPENDS += "curl"
DEPENDS_append_class-native = " fdupes-native"
DEPENDS_append_class-target = " fdupes-native"
DEPENDS += "libgcrypt"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup  -q -n gnupg-2.0.19
 cp ${S}/packaging/gpg2.manifest .
 
 
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
  
  # build PIEs (position independent executables) for address space randomisation:
  PIE="-fpie"
  export CFLAGS="$CFLAGS ${PIE}"
  export LDFLAGS=-pie
  
  
  autotools_do_configure
  
  oe_runmake ${PARALLEL_MAKE}
  
  
  
}
EXTRA_OECONF += " --libexecdir=${prefix}/lib --docdir=${prefix}/share/doc/packages/gpg2 --with-agent-pgm=${prefix}/bin/gpg-agent --with-scdaemon-pgm=${prefix}/bin/scdaemon --enable-gpgsm=yes --enable-gpg --with-gnu-ld --disable-doc"

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
 mkdir -p ${D}${sysconfdir}/gnupg/
 
 install -m 644 doc/examples/gpgconf.conf ${D}${sysconfdir}/gnupg
 
 rm -rf ${D}${prefix}/share/doc/packages/gpg2/examples/gpgconf.conf
 
 ln -sf gpg2 ${D}${prefix}/bin/gpg
 ln -sf gpgv2 ${D}${prefix}/bin/gpgv
 
 rm -rf ${D}${prefix}/share/locale/en@{bold,}quot
 rm -rf ${D}${prefix}/share/locale/en@{bold,}quot
 rm -fr ${D}${prefix}/share/doc
 
 #find_lang gnupg2
 
 #fdupes ${D}
 
 
}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " gpg2 "

gpg2_files = ""
gpg2_files += "${prefix}/bin/*"
gpg2_files += "${prefix}/lib/[^d]*"
gpg2_files += "${prefix}/sbin/addgnupghome"
gpg2_files += "${prefix}/sbin/applygnupgdefaults"
gpg2_files += "${prefix}/share/gnupg"
gpg2_files += "${sysconfdir}/gnupg/gpgconf.conf"
MANIFESTFILES_${PN} = "gpg2.manifest"

FILES_${PN} = "${gpg2_files}"

PKG_gpg2= "gpg2"

require gpg2-extraconf.inc

