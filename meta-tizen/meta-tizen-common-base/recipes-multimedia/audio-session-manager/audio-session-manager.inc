DESCRIPTION = "Audio Session Manager"
HOMEPAGE = "http://nohomepage.org"
SECTION = "Multimedia/Service"
LICENSE = "Apache-2.0"
PV = "0.2.6"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by audio-session-manager-dev
PROVIDES += "audio-session-manager-dev"


#PROVIDES by audio-session-manager


#PROVIDES by audio-session-manager-sdk-dev
PROVIDES += "audio-session-manager-sdk-dev"


RDEPENDS = ""
#RDEPENDS of audio-session-manager-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "audio-session-manager"

#RDEPENDS of audio-session-manager (${PN})
RDEPENDS_${PN} += "glibc"
RDEPENDS_${PN} += "vconf"

#RDEPENDS of audio-session-manager-sdk-dev (${PN}-sdk-dev)
RDEPENDS_${PN}-sdk-dev += "audio-session-manager-dev"


DEPENDS = ""
#DEPENDS of audio-session-manager
DEPENDS += "avsystem"
DEPENDS += "libmm-common"
inherit pkgconfig
DEPENDS += "glib-2.0"
DEPENDS += "system-server"
DEPENDS += "security-server"
DEPENDS += "vconf"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/audio-session-manager.manifest .
 
 
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
  
  CFLAGS="$CFLAGS -fvisibility=hidden -DMM_DEBUG_FLAG -DEXPORT_API=\"__attribute__((visibility(\\\"default\\\")))\"" ; export CFLAGS
  
  autotools_do_configure
  oe_runmake ${PARALLEL_MAKE}
  
  
  
}
EXTRA_OECONF += " --disable-static --enable-security "

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

pkg_postinst_${PN}() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
    vconftool set -t int memory/Sound/SoundStatus "0" -g 29 -f -i

}

pkg_postrm_${PN}() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " audio-session-manager-dev "
PACKAGES += " audio-session-manager "
PACKAGES += " audio-session-manager-sdk-dev "

audio-session-manager-dev_files = ""
audio-session-manager-dev_files += "${prefix}/include/mmf/audio-session-manager-types.h"
audio-session-manager-dev_files += "${prefix}/include/mmf/audio-session-manager.h"
MANIFESTFILES_${PN}-dev = "audio-session-manager.manifest"

audio-session-manager_files = ""
audio-session-manager_files += "${prefix}/lib/libaudio-session-mgr.so.*"
audio-session-manager_files += "${prefix}/bin/asm_testsuite"
MANIFESTFILES_${PN} = "audio-session-manager.manifest"

audio-session-manager-sdk-dev_files = ""
audio-session-manager-sdk-dev_files += "${prefix}/include/mmf/audio-session-manager-types.h"
audio-session-manager-sdk-dev_files += "${prefix}/include/mmf/audio-session-manager.h"
audio-session-manager-sdk-dev_files += "${prefix}/lib/libaudio-session-mgr.so"
audio-session-manager-sdk-dev_files += "${prefix}/lib/pkgconfig/audio-session-mgr.pc"
MANIFESTFILES_${PN}-sdk-dev = "audio-session-manager.manifest"

FILES_${PN}-dev = "${audio-session-manager-dev_files}"
FILES_${PN} = "${audio-session-manager_files}"
FILES_${PN}-sdk-dev = "${audio-session-manager-sdk-dev_files}"

PKG_audio-session-manager-dev= "audio-session-manager-dev"
PKG_audio-session-manager= "audio-session-manager"
PKG_audio-session-manager-sdk-dev= "audio-session-manager-sdk-dev"

require audio-session-manager-extraconf.inc

