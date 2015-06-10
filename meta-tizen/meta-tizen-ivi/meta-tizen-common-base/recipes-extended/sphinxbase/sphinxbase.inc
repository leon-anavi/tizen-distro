DESCRIPTION = "Speech Recognition Engine"
HOMEPAGE = "http://nohomepage.org"
SECTION = "System/Libraries"
LICENSE = "BSD-2-Clause"
PV = "0.7"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by sphinxbase-dev
PROVIDES += "sphinxbase-dev"


#PROVIDES by sphinxbase


#PROVIDES by sphinxbase-python
PROVIDES += "sphinxbase-python"


#PROVIDES by sphinxbase-libs
PROVIDES += "sphinxbase-libs"


RDEPENDS = ""
#RDEPENDS of sphinxbase-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "sphinxbase-libs"

#RDEPENDS of sphinxbase-python (${PN}-python)
RDEPENDS_${PN}-python += "sphinxbase-libs"


DEPENDS = ""
#DEPENDS of sphinxbase
inherit pythonnative
DEPENDS += "python-setuptools"
DEPENDS_append_class-native = " bison-native"
DEPENDS_append_class-target = " bison-native"
inherit pkgconfig

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 
 
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
EXTRA_OECONF += " --disable-static --disable-rpath"

do_install() {
 export RPM_BUILD_ROOT=${D}
 cd ${S}
 LANG=C
 export LANG
 unset DISPLAY
 rm -rf ${D}
 mkdir -p ${D}
 
 rm -rf ${D}
 mkdir -p ${D}${prefix}/lib/python2.7/site-packages
 
   oe_runmake \
         DESTDIR=${D} \
         INSTALL_ROOT=${D} \
         BINDIR=${prefix}/bin \
   install  
   rm -f ${D}${infodir}/dir 
   find ${D} -regex ".*\.la$" | xargs rm -f -- 
   find ${D} -regex ".*\.a$" | xargs rm -f --
 rm -f ${D}${prefix}/lib/*.la
 
 # Install the man pages
 mkdir -p ${D}${mandir}/man1
 cp -p doc/*.1 ${D}${mandir}/man1
 
 
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
PACKAGES += " sphinxbase-dev "
PACKAGES += " sphinxbase "
PACKAGES += " sphinxbase-libs "
PACKAGES += " sphinxbase-python "

sphinxbase-dev_files = ""
sphinxbase-dev_files += "${prefix}/include/sphinxbase"
sphinxbase-dev_files += "${prefix}/lib/libsphinxad.so"
sphinxbase-dev_files += "${prefix}/lib/libsphinxbase.so"
sphinxbase-dev_files += "${prefix}/lib/pkgconfig/sphinxbase.pc"

sphinxbase_files = ""
sphinxbase_files += "${prefix}/bin/*"
sphinxbase_files += "${mandir}/man1/*"

sphinxbase-libs_files = ""
sphinxbase-libs_files += "AUTHORS ChangeLog NEWS README"
sphinxbase-libs_files += "${prefix}/lib/libsphinxad.so.*"
sphinxbase-libs_files += "${prefix}/lib/libsphinxbase.so.*"

sphinxbase-python_files = ""
sphinxbase-python_files += "${prefix}/lib/python2.7/site-packages/*"

FILES_${PN}-dev = "${sphinxbase-dev_files}"
FILES_${PN} = "${sphinxbase_files}"
FILES_${PN}-libs = "${sphinxbase-libs_files}"
FILES_${PN}-python = "${sphinxbase-python_files}"

PKG_sphinxbase-dev= "sphinxbase-dev"
PKG_sphinxbase= "sphinxbase"
PKG_sphinxbase-libs= "sphinxbase-libs"
PKG_sphinxbase-python= "sphinxbase-python"

require sphinxbase-extraconf.inc

