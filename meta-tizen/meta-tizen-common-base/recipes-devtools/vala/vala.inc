DESCRIPTION = "Programming language for GNOME"
HOMEPAGE = "http://live.gnome.org/Vala"
SECTION = "Platform Development/Utilities"
LICENSE = "LGPL-2.0"
PV = "0.26.1"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by libvala
PROVIDES += "libvala"


#PROVIDES by vala


#PROVIDES by libvala-dev
PROVIDES += "libvala-dev"


RDEPENDS = ""
#RDEPENDS of vala (${PN})
RDEPENDS_${PN} += "update-alternatives"

#RDEPENDS of libvala-dev (lib${PN}-dev)
RDEPENDS_lib${PN}-dev += "libvala"


DEPENDS = ""
#DEPENDS of vala
DEPENDS += "xz"
DEPENDS += "flex"
DEPENDS_append_class-native = " fdupes-native"
DEPENDS_append_class-target = " fdupes-native"
DEPENDS_append_class-native = " bison-native"
DEPENDS_append_class-target = " bison-native"
DEPENDS += "glib-2.0"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/vala.manifest .
 
 
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
EXTRA_OECONF += " --with-pic --enable-vapigen"

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
 #fdupes ${D}${prefix}/share
 
 
}

pkg_postinst_libvala() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postinst_${PN}() {
    #!/bin/sh -e

    update-alternatives \
      --install $D${prefix}/bin/vala                          vala                     $D${prefix}/bin/vala-0.26 \
                26 \
      --slave   $D${prefix}/bin/valac                         valac                    $D${prefix}/bin/valac-0.26 \
      --slave   $D${prefix}/bin/vala-gen-introspect           vala-gen-introspect      $D${prefix}/bin/vala-gen-introspect-0.26 \
      --slave   $D${prefix}/bin/vapicheck                     vapicheck                $D${prefix}/bin/vapicheck-0.26 \
      --slave   $D${prefix}/bin/vapigen                       vapigen                  $D${prefix}/bin/vapigen-0.26 \
      --slave   ${mandir}/man1/valac.1.gz               valac.1.gz               ${mandir}/man1/valac-0.26.1.gz \
      --slave   ${mandir}/man1/vala-gen-introspect.1.gz vala-gen-introspect.1.gz ${mandir}/man1/vala-gen-introspect-0.26.1.gz \
      --slave   ${mandir}/man1/vapigen.1.gz             vapigen.1.gz             ${mandir}/man1/vapigen-0.26.1.gz \
      --slave   $D${prefix}/share/pkgconfig/vapigen.pc         vapigen.pc               $D${prefix}/share/pkgconfig/vapigen-0.26.pc

}

pkg_postrm_${PN}() {
    #!/bin/sh -e

    # Note: we don't use "$1 -eq 0", to avoid issues if the package gets renamed
    if [ ! -f $D${prefix}/bin/vala-0.26 ]; then
      update-alternatives --remove vala $D${prefix}/bin/vala-0.26
    fi

}

pkg_postrm_libvala() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " libvala "
PACKAGES += " vala "
PACKAGES += " libvala-dev "

libvala_files = ""
libvala_files += "${prefix}/lib/libvala-0.26.so.*"
MANIFESTFILES_lib${PN} = "vala.manifest"

vala_files = ""
vala_files += "${prefix}/bin/vala-0.26"
vala_files += "${prefix}/bin/valac-0.26"
vala_files += "${prefix}/bin/vala-gen-introspect-0.26"
vala_files += "${prefix}/bin/vapicheck-0.26"
vala_files += "${prefix}/bin/vapigen-0.26"
vala_files += "${mandir}/man1/valac-0.26.1*"
vala_files += "${mandir}/man1/vala-gen-introspect-0.26.1*"
vala_files += "${mandir}/man1/vapigen-0.26.1*"
vala_files += "${prefix}/share/aclocal/vala.m4"
vala_files += "${prefix}/share/aclocal/vapigen.m4"
vala_files += "${prefix}/share/pkgconfig/vapigen-0.26.pc"
vala_files += "${prefix}/share/vala"
vala_files += "${prefix}/share/vala/Makefile.vapigen"
vala_files += "${prefix}/share/vala-0.26/"
vala_files += "${prefix}/lib/vala-0.26/"
MANIFESTFILES_${PN} = "vala.manifest"
DIRFILES_${PN} = ""
DIRFILES_${PN} += "${prefix}/share/vala"

libvala-dev_files = ""
libvala-dev_files += "AUTHORS ChangeLog NEWS README"
libvala-dev_files += "${prefix}/include/vala-0.26/"
libvala-dev_files += "${prefix}/lib/libvala-0.26.so"
libvala-dev_files += "${prefix}/lib/pkgconfig/libvala-0.26.pc"
MANIFESTFILES_lib${PN}-dev = "vala.manifest"

FILES_lib${PN} = "${libvala_files}"
FILES_${PN} = "${vala_files}"
FILES_lib${PN}-dev = "${libvala-dev_files}"

PKG_libvala= "libvala"
PKG_vala= "vala"
PKG_libvala-dev= "libvala-dev"

require vala-extraconf.inc

