DESCRIPTION = "MMSound Package contains client lib and sound_server binary"
HOMEPAGE = "http://nohomepage.org"
SECTION = "Multimedia/Media Playback"
LICENSE = "Apache-2.0"
PV = "0.7.2h"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by libmm-sound-dev
PROVIDES += "libmm-sound-dev"


#PROVIDES by libmm-sound


#PROVIDES by libmm-sound-tool
PROVIDES += "libmm-sound-tool"


#PROVIDES by libmm-sound-sdk-dev
PROVIDES += "libmm-sound-sdk-dev"


#PROVIDES by sound-server
PROVIDES += "sound-server"


RDEPENDS = ""
#RDEPENDS of libmm-sound-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "libmm-sound"

#RDEPENDS of libmm-sound-sdk-dev (${PN}-sdk-dev)
RDEPENDS_${PN}-sdk-dev += "libmm-sound-dev"

#RDEPENDS of libmm-sound-tool (${PN}-tool)
RDEPENDS_${PN}-tool += "libmm-sound"

#RDEPENDS of libmm-sound (${PN})
RDEPENDS_${PN} += "glibc"
RDEPENDS_${PN} += "vconf"

#RDEPENDS of sound-server (sound-server)
RDEPENDS_sound-server += "libmm-sound"


DEPENDS = ""
#DEPENDS of libmm-sound
DEPENDS += "avsystem"
DEPENDS += "libmm-common"
DEPENDS += "audio-session-manager"
DEPENDS += "libmm-log"
inherit pkgconfig
DEPENDS += "glib-2.0"
DEPENDS += "system-server"
DEPENDS += "vconf"
DEPENDS += "security-server"
DEPENDS += "heynoti"
DEPENDS += "libmm-session"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/libmm-sound.manifest .
 
 
 
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
  
  ./autogen.sh
  CFLAGS="$CFLAGS -fvisibility=hidden -DMM_DEBUG_FLAG -DSEPARATE_SPEAKER_AND_WIRED_ACCESSORY -DEXPORT_API=\"__attribute__((visibility(\\\"default\\\")))\""; export CFLAGS
  CFLAGS="$CFLAGS -DMURPHY"; export CFLAGS
  
  autotools_do_configure
  oe_runmake ${PARALLEL_MAKE}
  
  
  
  
}
EXTRA_OECONF += " --prefix=/usr --enable-pulse --enable-security --enable-policy"

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
 install -d ${D}${systemd_unitdir}/system/multi-user.target.wants
 install -m0644 ${S}/packaging/sound-server.service ${D}${systemd_unitdir}/system/
 install -m0644 ${S}/packaging/sound-server.path ${D}${systemd_unitdir}/system/
 
 
 mkdir -p ${D}/${systemd_unitdir}/system/multi-user.target.wants 
 ln -s ../sound-server.path  ${D}/${systemd_unitdir}/system/multi-user.target.wants/sound-server.path  
 
 
}

pkg_postinst_${PN}() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
    /usr/bin/vconftool set -t int memory/Sound/ASMReady 0 -g 29 -f -i
    /usr/bin/vconftool set -t int file/private/sound/volume/system 5 -g 29 -f
    /usr/bin/vconftool set -t int file/private/sound/volume/notification 7 -g 29 -f
    /usr/bin/vconftool set -t int file/private/sound/volume/alarm 7 -g 29 -f
    /usr/bin/vconftool set -t int file/private/sound/volume/ringtone 13 -g 29 -f
    /usr/bin/vconftool set -t int file/private/sound/volume/media 7 -g 29 -f
    /usr/bin/vconftool set -t int file/private/sound/volume/call 7 -g 29 -f
    /usr/bin/vconftool set -t int file/private/sound/volume/voip 7 -g 29 -f
    /usr/bin/vconftool set -t int file/private/sound/volume/fixed 0 -g 29 -f
    /usr/bin/vconftool set -t int file/private/sound/volume/java 11 -g 29 -f

}

pkg_postinst_sound-server() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_sound-server() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_${PN}() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " libmm-sound-dev "
PACKAGES += " libmm-sound-sdk-dev "
PACKAGES += " libmm-sound-tool "
PACKAGES += " libmm-sound "
PACKAGES += " sound-server "

libmm-sound-dev_files = ""
libmm-sound-dev_files += "${prefix}/lib/libmmfkeysound.so"
libmm-sound-dev_files += "${prefix}/lib/libmmfsound.so"
libmm-sound-dev_files += "${prefix}/lib/libmmfsoundcommon.so"
libmm-sound-dev_files += "${prefix}/include/mmf/mm_sound_private.h"
libmm-sound-dev_files += "${prefix}/include/mmf/mm_sound_plugin.h"
libmm-sound-dev_files += "${prefix}/include/mmf/mm_sound_plugin_hal.h"
MANIFESTFILES_${PN}-dev = "libmm-sound.manifest"

libmm-sound-sdk-dev_files = ""
libmm-sound-sdk-dev_files += "${prefix}/include/mmf/mm_sound.h"
libmm-sound-sdk-dev_files += "${prefix}/lib/pkgconfig/mm-keysound.pc"
libmm-sound-sdk-dev_files += "${prefix}/lib/pkgconfig/mm-sound.pc"
MANIFESTFILES_${PN}-sdk-dev = "libmm-sound.manifest"

libmm-sound-tool_files = ""
libmm-sound-tool_files += "${prefix}/bin/mm_sound_testsuite"
MANIFESTFILES_${PN}-tool = "libmm-sound.manifest"

libmm-sound_files = ""
libmm-sound_files += "${prefix}/lib/libmmfsound.so.*"
libmm-sound_files += "${prefix}/lib/libmmfsoundcommon.so.*"
libmm-sound_files += "${prefix}/lib/libmmfkeysound.so.*"
MANIFESTFILES_${PN} = "libmm-sound.manifest"

sound-server_files = ""
sound-server_files += "${prefix}/bin/sound_server"
sound-server_files += "${prefix}/lib/libsoundplugintone.so*"
sound-server_files += "${prefix}/lib/libsoundpluginwave.so*"
sound-server_files += "${prefix}/lib/libsoundpluginkeytone.so*"
sound-server_files += "${prefix}/lib/soundplugins/libsoundplugintone.so"
sound-server_files += "${prefix}/lib/soundplugins/libsoundpluginwave.so"
sound-server_files += "${prefix}/lib/soundplugins/libsoundpluginkeytone.so"
sound-server_files += "${prefix}/share/sounds/sound-server/*"
sound-server_files += "${systemd_unitdir}/system/multi-user.target.wants/sound-server.path"
sound-server_files += "${systemd_unitdir}/system/sound-server.service"
sound-server_files += "${systemd_unitdir}/system/sound-server.path"
MANIFESTFILES_sound-server = "libmm-sound.manifest"

FILES_${PN}-dev = "${libmm-sound-dev_files}"
FILES_${PN}-sdk-dev = "${libmm-sound-sdk-dev_files}"
FILES_${PN}-tool = "${libmm-sound-tool_files}"
FILES_${PN} = "${libmm-sound_files}"
FILES_sound-server = "${sound-server_files}"

PKG_libmm-sound-dev= "libmm-sound-dev"
PKG_libmm-sound-sdk-dev= "libmm-sound-sdk-dev"
PKG_libmm-sound-tool= "libmm-sound-tool"
PKG_libmm-sound= "libmm-sound"
PKG_sound-server= "sound-server"

require libmm-sound-extraconf.inc

