DESCRIPTION = "Utilities for Manipulating Desktop Files"
HOMEPAGE = "http://www.freedesktop.org/wiki/Software/desktop-file-utils"
SECTION = "Development/Tools/Other"
LICENSE = "GPL-2.0+"
PV = "0.20"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by desktop-file-utils


RDEPENDS = ""

DEPENDS = ""
#DEPENDS of desktop-file-utils
DEPENDS += "xz"
inherit pkgconfig
DEPENDS += "glib-2.0"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/desktop-file-utils.manifest .
 
 
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
  oe_runmake ${PARALLEL_MAKE}
  
  
  
}
EXTRA_OECONF += " --with-lispdir=${prefix}/share/emacs/site-lisp"

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
         BINDIR=${prefix}/bin \
         prefix=${prefix} \
         exec_prefix=${prefix} \
         bindir=${prefix}/bin \
         sbindir=${prefix}/sbin \
         sysconfdir=${sysconfdir} \
         datadir=${prefix}/share \
         includedir=${prefix}/include \
         libdir=${prefix}/lib \
         libexecdir=${prefix}/libexec \
         localstatedir=}${localstatedir} \
         sharedstatedir=${prefix}/com \
         mandir=${mandir} \
         infodir=${infodir} \
   install
 # we don't want to buildrequire emacs, but recent automake make it
 # impossible to install a lisp file without emacs installed. So we
 # manually do it.
 test ! -f ${D}${prefix}/share/emacs/site-lisp/desktop-entry-mode.el
 install -D -m644 misc/desktop-entry-mode.el ${D}${prefix}/share/emacs/site-lisp/desktop-entry-mode.el
 # Install rpm macros
 install -D -m644 ${S}/packaging/macros.desktop-file-utils ${D}${sysconfdir}/rpm/macros.desktop-file-utils
 # Create ghosts based on default $XDG_DATA_DIRS:
 mkdir -p ${D}${prefix}/share/applications
 touch ${D}${prefix}/share/applications/mimeinfo.cache
 
 
}

pkg_postinst_${PN}() {
    #!/bin/sh -e

    $D${prefix}/bin/update-desktop-database --quiet $D${prefix}/share/applications || true

}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " desktop-file-utils "

desktop-file-utils_files = ""
desktop-file-utils_files += "AUTHORS ChangeLog NEWS README"
desktop-file-utils_files += "${prefix}/bin/desktop-file-edit"
desktop-file-utils_files += "${prefix}/bin/desktop-file-install"
desktop-file-utils_files += "${prefix}/bin/desktop-file-validate"
desktop-file-utils_files += "${prefix}/bin/update-desktop-database"
desktop-file-utils_files += "${mandir}/man1/desktop-file-edit.1*"
desktop-file-utils_files += "${mandir}/man1/desktop-file-install.1*"
desktop-file-utils_files += "${mandir}/man1/desktop-file-validate.1*"
desktop-file-utils_files += "${mandir}/man1/update-desktop-database.1*"
desktop-file-utils_files += "${prefix}/share/emacs"
desktop-file-utils_files += "${prefix}/share/emacs/site-lisp"
desktop-file-utils_files += "${prefix}/share/emacs/site-lisp/*.el*"
desktop-file-utils_files += "${sysconfdir}/rpm/macros.desktop-file-utils"
MANIFESTFILES_${PN} = "desktop-file-utils.manifest"
DIRFILES_${PN} = ""
DIRFILES_${PN} += "${prefix}/share/emacs"
DIRFILES_${PN} += "${prefix}/share/emacs/site-lisp"

FILES_${PN} = "${desktop-file-utils_files}"

PKG_desktop-file-utils= "desktop-file-utils"

require desktop-file-utils-extraconf.inc

