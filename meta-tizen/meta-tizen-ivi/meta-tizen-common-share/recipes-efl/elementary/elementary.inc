DESCRIPTION = "EFL toolkit for small touchscreens"
HOMEPAGE = "http://trac.enlightenment.org/e/wiki/Elementary"
SECTION = "Graphics & UI Framework/Development"
LICENSE = "LGPL-2.1+"
PV = "1.12.2"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by elementary


#PROVIDES by elementary-tools
PROVIDES += "elementary-tools"


#PROVIDES by elementary-dev
PROVIDES += "elementary-dev"


#PROVIDES by elementary-examples
PROVIDES += "elementary-examples"


RDEPENDS = ""
#RDEPENDS of elementary-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "elementary"


DEPENDS = ""
#DEPENDS of elementary
DEPENDS += "edje"
DEPENDS += "ethumb"
DEPENDS += "edbus"
inherit pythonnative
DEPENDS += "eet"
inherit pkgconfig
#Replace "DEPENDS" on gettext by "inherit gettext"
inherit gettext
DEPENDS += "efreet"
DEPENDS += "eina"
DEPENDS += "eolian-dev"
DEPENDS += "efl"
DEPENDS += "evas"
DEPENDS += "ecore"
DEPENDS += "emotion"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/elementary.manifest .
 
 
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
EXTRA_OECONF += " --disable-static --enable-ecore-wayland --disable-ecore-x --disable-build-examples"

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
 
 #find_lang elementary
 
 
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
PACKAGES += " elementary-tools "
PACKAGES += " elementary "
PACKAGES += " elementary-dev "

elementary-tools_files = ""
elementary-tools_files += "${prefix}/share/applications/*"
elementary-tools_files += "${prefix}/bin/elementary_config"
elementary-tools_files += "${prefix}/bin/elementary_test*"
elementary-tools_files += "${prefix}/bin/elementary_codegen"
elementary-tools_files += "${prefix}/bin/elm_prefs_cc"
MANIFESTFILES_${PN}-tools = "elementary.manifest"

elementary_files = ""
elementary_files += "${prefix}/bin/elementary_quicklaunch"
elementary_files += "${prefix}/bin/elementary_run"
elementary_files += "${prefix}/lib/edje/*"
elementary_files += "${prefix}/lib/elementary/modules/*"
elementary_files += "${prefix}/lib/*.so.*"
elementary_files += "${prefix}/share/elementary/*"
elementary_files += "${prefix}/share/icons/elementary.png"
MANIFESTFILES_${PN} = "elementary.manifest"

elementary-dev_files = ""
elementary-dev_files += "${prefix}/include/elementary-1/*.h*"
elementary-dev_files += "${prefix}/share/eolian/include/elementary-1/*.eo"
elementary-dev_files += "${prefix}/lib/*.so"
elementary-dev_files += "${prefix}/lib/pkgconfig/*.pc"
elementary-dev_files += "${prefix}/lib/cmake/Elementary/ElementaryConfig.cmake"
elementary-dev_files += "${prefix}/lib/cmake/Elementary/ElementaryConfigVersion.cmake"
MANIFESTFILES_${PN}-dev = "elementary.manifest"

FILES_${PN}-tools = "${elementary-tools_files}"
FILES_${PN} = "${elementary_files}"
FILES_${PN}-dev = "${elementary-dev_files}"

PKG_elementary-tools= "elementary-tools"
PKG_elementary= "elementary"
PKG_elementary-dev= "elementary-dev"

require elementary-extraconf.inc

