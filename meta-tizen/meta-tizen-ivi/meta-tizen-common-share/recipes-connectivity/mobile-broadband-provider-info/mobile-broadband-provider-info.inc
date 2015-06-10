DESCRIPTION = "Moblie Broadband Dataprovider Database"
HOMEPAGE = "http://www.gnome.org"
SECTION = "Applications/Internet"
LICENSE = "Creative Commons Public Domain"
PV = "20120614"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by mobile-broadband-provider-info


RDEPENDS = ""

DEPENDS = ""

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/mobile-broadband-provider-info.manifest .
 
 
 
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
EXTRA_OECONF += " --disable-static"

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

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " mobile-broadband-provider-info "

mobile-broadband-provider-info_files = ""
mobile-broadband-provider-info_files += "${prefix}/share/pkgconfig/mobile-broadband-provider-info.pc"
mobile-broadband-provider-info_files += "${prefix}/share/mobile-broadband-provider-info/*"
MANIFESTFILES_${PN} = "mobile-broadband-provider-info.manifest"

FILES_${PN} = "${mobile-broadband-provider-info_files}"

PKG_mobile-broadband-provider-info= "mobile-broadband-provider-info"

require mobile-broadband-provider-info-extraconf.inc

