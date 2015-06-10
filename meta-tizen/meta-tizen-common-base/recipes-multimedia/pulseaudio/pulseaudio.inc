DESCRIPTION = "Improved Linux sound server"
HOMEPAGE = "http://nohomepage.org"
SECTION = "Multimedia/Audio"
LICENSE = "GPL-2.0+ and LGPL-2.1+"
PV = "5.0"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by libpulse
PROVIDES += "libpulse"


#PROVIDES by pulseaudio-vala-bindings
PROVIDES += "pulseaudio-vala-bindings"


#PROVIDES by pulseaudio-module-dbus-protocol
PROVIDES += "pulseaudio-module-dbus-protocol"


#PROVIDES by pulseaudio-realtime-scheduling
PROVIDES += "pulseaudio-realtime-scheduling"


#PROVIDES by pulseaudio-module-null-source
PROVIDES += "pulseaudio-module-null-source"


#PROVIDES by pulseaudio-module-combine-sink
PROVIDES += "pulseaudio-module-combine-sink"


#PROVIDES by libpulse-mainloop-glib
PROVIDES += "libpulse-mainloop-glib"


#PROVIDES by pulseaudio-module-raop
PROVIDES += "pulseaudio-module-raop"


#PROVIDES by pulseaudio-config
PROVIDES += "pulseaudio-config"


#PROVIDES by pulseaudio-utils
PROVIDES += "pulseaudio-utils"


#PROVIDES by pulseaudio-module-augment-properties
PROVIDES += "pulseaudio-module-augment-properties"


#PROVIDES by pulseaudio


#PROVIDES by pulseaudio-docs
PROVIDES += "pulseaudio-docs "


#PROVIDES by libpulse-dev
PROVIDES += "libpulse-dev"


#PROVIDES by pulseaudio-module-filter
PROVIDES += "pulseaudio-module-filter"


#PROVIDES by pulseaudio-module-bluetooth
PROVIDES += "pulseaudio-module-bluetooth"


#PROVIDES by pulseaudio-module-switch-on-connect
PROVIDES += "pulseaudio-module-switch-on-connect"


#PROVIDES by pulseaudio-module-dev
PROVIDES += "pulseaudio-module-dev"


RDEPENDS = ""
#RDEPENDS of pulseaudio-vala-bindings (${PN}-vala-bindings)
RDEPENDS_${PN}-vala-bindings += "pulseaudio"

#RDEPENDS of pulseaudio (${PN})
RDEPENDS_${PN} += "glibc"
RDEPENDS_${PN} += "udev"

#RDEPENDS of pulseaudio-realtime-scheduling (${PN}-realtime-scheduling)
RDEPENDS_${PN}-realtime-scheduling += "libcap"
RDEPENDS_${PN}-realtime-scheduling += "pulseaudio"

#RDEPENDS of pulseaudio-utils (${PN}-utils)
RDEPENDS_${PN}-utils += "pulseaudio"

#RDEPENDS of pulseaudio-module-dev (${PN}-module-dev)
RDEPENDS_${PN}-module-dev += "pulseaudio"

#RDEPENDS of libpulse-dev (libpulse-dev)
RDEPENDS_libpulse-dev += "libpulse"
RDEPENDS_libpulse-dev += "libpulse-mainloop-glib"

#RDEPENDS of pulseaudio-module-bluetooth (${PN}-module-bluetooth)
RDEPENDS_${PN}-module-bluetooth += "pulseaudio"


DEPENDS = ""
#DEPENDS of pulseaudio
DEPENDS += "speex"
DEPENDS += "libsndfile1"
DEPENDS_append_class-native = " intltool-native"
DEPENDS_append_class-target = " intltool-native"
DEPENDS += "sbc"
DEPENDS += "openssl"
DEPENDS += "alsa-lib"
DEPENDS += "dbus"
inherit pkgconfig
DEPENDS += "udev"
DEPENDS += "glib-2.0"
DEPENDS += "bluez5"
DEPENDS += "systemd"
DEPENDS_append_class-native = " libtool"
DEPENDS_append_class-target = " libtool-cross"
DEPENDS += "tdb"
DEPENDS += "gconf"
DEPENDS += "libcap"
DEPENDS += "json-c"
DEPENDS_append_class-native = " fdupes-native"
DEPENDS_append_class-target = " fdupes-native"
DEPENDS += "vconf"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q -T -b0
 echo "5.0" > .tarball-version
 cp ${S}/packaging/pulseaudio.manifest .
 
 
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
  
  export CFLAGS="$CFLAGS -fno-strict-aliasing"
  export LD_AS_NEEDED=0
  NOCONFIGURE=yes ./bootstrap.sh
  
  autotools_do_configure
  
  oe_runmake ${PARALLEL_MAKE} V=0
  
  
  
}
EXTRA_OECONF += " --prefix=${prefix} --disable-static --enable-alsa --disable-ipv6 --disable-oss-output --disable-oss-wrapper --disable-x11 --disable-hal-compat --disable-lirc --disable-avahi --disable-jack --disable-xen --without-fftw --enable-bluez5 --disable-bluez4 --with-bluetooth-headset-backend=ofono --enable-systemd --with-database=tdb --enable-samsung-policy --with-udev-rules-dir=${prefix}/lib/udev/rules.d --with-system-user=pulse --with-system-group=pulse --with-access-group=pulse-access"

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
 #find_lang pulseaudio
 
 CURDIR=$(pwd)
 cd ${D}${sysconfdir}/pulse/filter
 ln -sf filter_8000_44100.dat filter_11025_44100.dat
 ln -sf filter_8000_44100.dat filter_12000_44100.dat
 ln -sf filter_8000_44100.dat filter_16000_44100.dat
 ln -sf filter_8000_44100.dat filter_22050_44100.dat
 ln -sf filter_8000_44100.dat filter_24000_44100.dat
 ln -sf filter_8000_44100.dat filter_32000_44100.dat
 cd ${CURDIR}
 
 rm -rf  ${D}${sysconfdir}/xdg/autostart/pulseaudio-kde.desktop
 rm -rf  ${D}${prefix}/bin/start-pulseaudio-kde
 rm -rf  ${D}${prefix}/bin/start-pulseaudio-x11
 rm -rf ${D}${prefix}/lib/pulse-5.0/modules/module-device-manager.so
 
 mkdir -p ${D}${prefix}/include/pulsemodule/pulse
 mkdir -p ${D}${prefix}/include/pulsemodule/pulsecore
 
 cp ${D}${prefix}/include/pulse/*.h ${D}${prefix}/include/pulsemodule/pulse
 
 fdupes  ${D}${prefix}/share
 fdupes  ${D}${prefix}/include
 
 # get rid of *.la files
 rm -f ${D}${prefix}/lib/*.la
 rm -f ${D}${prefix}/lib/pulseaudio/*.la
 
 
}

pkg_postinst_${PN}() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
    if [ $1 -eq 1 ] ; then
    # Initial installation
    systemctl --user --global preset pulseaudio.socket >/dev/null 2>&1 || :
    fi

}

pkg_postinst_libpulse-mainloop-glib() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postinst_libpulse() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postinst_${PN}() {
    #!/bin/sh -e

    setcap cap_sys_nice+ep /usr/bin/pulseaudio

}

pkg_prerm_${PN}() {
    #!/bin/sh -e

    if [ $1 -eq 0 ] ; then
    # Package removal, not upgrade
    systemctl --no-reload --user --global disable pulseaudio.socket > /dev/null 2>&1 || :
    fi

}

pkg_postrm_libpulse() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_libpulse-mainloop-glib() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_${PN}() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_${PN}() {
    #!/bin/sh -e

    setcap -r /usr/bin/pulseaudio
    #lang_package

}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " pulseaudio-module-filter "
PACKAGES += " libpulse "
PACKAGES += " pulseaudio-module-dbus-protocol "
PACKAGES += " pulseaudio-realtime-scheduling "
PACKAGES += " pulseaudio-module-combine-sink "
PACKAGES += " pulseaudio-module-bluetooth "
PACKAGES += " pulseaudio-utils "
PACKAGES += " pulseaudio-module-raop "
PACKAGES += " pulseaudio-config "
PACKAGES += " libpulse-mainloop-glib "
PACKAGES += " pulseaudio-module-augment-properties "
PACKAGES += " pulseaudio "
PACKAGES += " pulseaudio-module-dev "
PACKAGES += " libpulse-dev "
PACKAGES += " pulseaudio-vala-bindings "
PACKAGES += " pulseaudio-module-switch-on-connect "
PACKAGES += " pulseaudio-docs "
PACKAGES += " pulseaudio-module-null-source "

pulseaudio-module-filter_files = ""
pulseaudio-module-filter_files += "${prefix}/lib/pulse-5.0/modules/module-filter-*.so"
MANIFESTFILES_${PN}-module-filter = "pulseaudio.manifest"

libpulse_files = ""
libpulse_files += "${prefix}/lib/libpulse.so.*"
libpulse_files += "${prefix}/lib/libpulse-simple.so.*"
libpulse_files += "${prefix}/lib/pulseaudio/libpulsecommon-*.so"
MANIFESTFILES_libpulse = "pulseaudio.manifest"

pulseaudio-module-dbus-protocol_files = ""
pulseaudio-module-dbus-protocol_files += "${prefix}/lib/pulse-5.0/modules/module-dbus-protocol.so"
MANIFESTFILES_${PN}-module-dbus-protocol = "pulseaudio.manifest"

pulseaudio-realtime-scheduling_files = ""

pulseaudio-module-combine-sink_files = ""
pulseaudio-module-combine-sink_files += "${prefix}/lib/pulse-5.0/modules/module-combine-sink.so"
MANIFESTFILES_${PN}-module-combine-sink = "pulseaudio.manifest"

pulseaudio-module-bluetooth_files = ""
pulseaudio-module-bluetooth_files += "${prefix}/lib/pulse-5.0/modules/module-bluetooth-discover.so"
pulseaudio-module-bluetooth_files += "${prefix}/lib/pulse-5.0/modules/module-bluetooth-policy.so"
pulseaudio-module-bluetooth_files += "${prefix}/lib/pulse-5.0/modules/module-bluez5-discover.so"
pulseaudio-module-bluetooth_files += "${prefix}/lib/pulse-5.0/modules/module-bluez5-device.so"
pulseaudio-module-bluetooth_files += "${prefix}/lib/pulse-5.0/modules/libbluez5-util.so"
MANIFESTFILES_${PN}-module-bluetooth = "pulseaudio.manifest"

pulseaudio-utils_files = ""
pulseaudio-utils_files += "${mandir}/man1/*"
pulseaudio-utils_files += "${mandir}/man5/*"
pulseaudio-utils_files += "${prefix}/bin/pacat"
pulseaudio-utils_files += "${prefix}/bin/pacmd"
pulseaudio-utils_files += "${prefix}/bin/pactl"
pulseaudio-utils_files += "${prefix}/bin/paplay"
pulseaudio-utils_files += "${prefix}/bin/parec"
pulseaudio-utils_files += "${prefix}/bin/pamon"
pulseaudio-utils_files += "${prefix}/bin/parecord"
pulseaudio-utils_files += "${prefix}/bin/pasuspender"
MANIFESTFILES_${PN}-utils = "pulseaudio.manifest"

pulseaudio-module-raop_files = ""
pulseaudio-module-raop_files += "${prefix}/lib/pulse-5.0/modules/libraop.so"
pulseaudio-module-raop_files += "${prefix}/lib/pulse-5.0/modules/module-raop*.so"
MANIFESTFILES_${PN}-module-raop = "pulseaudio.manifest"

pulseaudio-config_files = ""
pulseaudio-config_files += "${sysconfdir}/pulse/daemon.conf"
pulseaudio-config_files += "${sysconfdir}/pulse/default.pa"
pulseaudio-config_files += "${sysconfdir}/pulse/client.conf"
pulseaudio-config_files += "${sysconfdir}/pulse/system.pa"
pulseaudio-config_files += "${sysconfdir}/pulse/audio-groups.conf"
pulseaudio-config_files += "${sysconfdir}/pulse/main-volume-policy.conf"
pulseaudio-config_files += "${prefix}/share/pulseaudio/alsa-mixer/paths/*"
pulseaudio-config_files += "${prefix}/share/pulseaudio/alsa-mixer/profile-sets/*"
MANIFESTFILES_${PN}-config = "pulseaudio.manifest"

libpulse-mainloop-glib_files = ""
libpulse-mainloop-glib_files += "${prefix}/lib/libpulse-mainloop-glib.so.*"
MANIFESTFILES_libpulse-mainloop-glib = "pulseaudio.manifest"

pulseaudio-module-augment-properties_files = ""
pulseaudio-module-augment-properties_files += "${prefix}/lib/pulse-5.0/modules/module-augment-properties.so"
MANIFESTFILES_${PN}-module-augment-properties = "pulseaudio.manifest"

pulseaudio_files = ""
pulseaudio_files += "${sysconfdir}/pulse/filter/*.dat"
pulseaudio_files += "${prefix}/bin/esdcompat"
pulseaudio_files += "${prefix}/bin/pulseaudio"
pulseaudio_files += "${prefix}/libexec/pulse/*"
pulseaudio_files += "${prefix}/lib/libpulsecore-5.0.so"
pulseaudio_files += "${prefix}/lib/udev/rules.d/90-pulseaudio.rules"
pulseaudio_files += "/etc/dbus-1/system.d/pulseaudio-system.conf"
pulseaudio_files += "${prefix}/lib/pulse-5.0/modules/libalsa-util.so"
pulseaudio_files += "${prefix}/lib/pulse-5.0/modules/libcli.so"
pulseaudio_files += "${prefix}/lib/pulse-5.0/modules/libprotocol-cli.so"
pulseaudio_files += "${prefix}/lib/pulse-5.0/modules/libprotocol-http.so"
pulseaudio_files += "${prefix}/lib/pulse-5.0/modules/libprotocol-native.so"
pulseaudio_files += "${prefix}/lib/pulse-5.0/modules/libprotocol-simple.so"
pulseaudio_files += "${prefix}/lib/pulse-5.0/modules/librtp.so"
pulseaudio_files += "${prefix}/lib/pulse-5.0/modules/module-alsa-sink.so"
pulseaudio_files += "${prefix}/lib/pulse-5.0/modules/module-alsa-source.so"
pulseaudio_files += "${prefix}/lib/pulse-5.0/modules/module-always-sink.so"
pulseaudio_files += "${prefix}/lib/pulse-5.0/modules/module-console-kit.so"
pulseaudio_files += "${prefix}/lib/pulse-5.0/modules/module-device-restore.so"
pulseaudio_files += "${prefix}/lib/pulse-5.0/modules/module-stream-restore.so"
pulseaudio_files += "${prefix}/lib/pulse-5.0/modules/module-cli-protocol-tcp.so"
pulseaudio_files += "${prefix}/lib/pulse-5.0/modules/module-cli-protocol-unix.so"
pulseaudio_files += "${prefix}/lib/pulse-5.0/modules/module-cli.so"
pulseaudio_files += "${prefix}/lib/pulse-5.0/modules/module-combine.so"
pulseaudio_files += "${prefix}/lib/pulse-5.0/modules/module-default-device-restore.so"
pulseaudio_files += "${prefix}/lib/pulse-5.0/modules/module-detect.so"
pulseaudio_files += "${prefix}/lib/pulse-5.0/modules/module-esound-sink.so"
pulseaudio_files += "${prefix}/lib/pulse-5.0/modules/module-http-protocol-tcp.so"
pulseaudio_files += "${prefix}/lib/pulse-5.0/modules/module-http-protocol-unix.so"
pulseaudio_files += "${prefix}/lib/pulse-5.0/modules/module-intended-roles.so"
pulseaudio_files += "${prefix}/lib/pulse-5.0/modules/module-ladspa-sink.so"
pulseaudio_files += "${prefix}/lib/pulse-5.0/modules/module-match.so"
pulseaudio_files += "${prefix}/lib/pulse-5.0/modules/module-mmkbd-evdev.so"
pulseaudio_files += "${prefix}/lib/pulse-5.0/modules/module-native-protocol-fd.so"
pulseaudio_files += "${prefix}/lib/pulse-5.0/modules/module-native-protocol-tcp.so"
pulseaudio_files += "${prefix}/lib/pulse-5.0/modules/module-native-protocol-unix.so"
pulseaudio_files += "${prefix}/lib/pulse-5.0/modules/module-null-sink.so"
pulseaudio_files += "${prefix}/lib/pulse-5.0/modules/module-pipe-sink.so"
pulseaudio_files += "${prefix}/lib/pulse-5.0/modules/module-pipe-source.so"
pulseaudio_files += "${prefix}/lib/pulse-5.0/modules/module-position-event-sounds.so"
pulseaudio_files += "${prefix}/lib/pulse-5.0/modules/module-remap-sink.so"
pulseaudio_files += "${prefix}/lib/pulse-5.0/modules/module-remap-source.so"
pulseaudio_files += "${prefix}/lib/pulse-5.0/modules/module-rescue-streams.so"
pulseaudio_files += "${prefix}/lib/pulse-5.0/modules/module-rtp-recv.so"
pulseaudio_files += "${prefix}/lib/pulse-5.0/modules/module-rtp-send.so"
pulseaudio_files += "${prefix}/lib/pulse-5.0/modules/module-simple-protocol-tcp.so"
pulseaudio_files += "${prefix}/lib/pulse-5.0/modules/module-simple-protocol-unix.so"
pulseaudio_files += "${prefix}/lib/pulse-5.0/modules/module-sine.so"
pulseaudio_files += "${prefix}/lib/pulse-5.0/modules/module-tunnel-sink.so"
pulseaudio_files += "${prefix}/lib/pulse-5.0/modules/module-tunnel-sink-new.so"
pulseaudio_files += "${prefix}/lib/pulse-5.0/modules/module-tunnel-source.so"
pulseaudio_files += "${prefix}/lib/pulse-5.0/modules/module-tunnel-source-new.so"
pulseaudio_files += "${prefix}/lib/pulse-5.0/modules/module-suspend-on-idle.so"
pulseaudio_files += "${prefix}/lib/pulse-5.0/modules/module-volume-restore.so"
pulseaudio_files += "${prefix}/lib/pulse-5.0/modules/module-alsa-card.so"
pulseaudio_files += "${prefix}/lib/pulse-5.0/modules/module-card-restore.so"
pulseaudio_files += "${prefix}/lib/pulse-5.0/modules/module-sine-source.so"
pulseaudio_files += "${prefix}/lib/pulse-5.0/modules/module-loopback.so"
pulseaudio_files += "${prefix}/lib/pulse-5.0/modules/module-rygel-media-server.so"
pulseaudio_files += "${prefix}/lib/pulse-5.0/modules/module-echo-cancel.so"
pulseaudio_files += "${prefix}/lib/pulse-5.0/modules/module-virtual-sink.so"
pulseaudio_files += "${prefix}/lib/pulse-5.0/modules/module-virtual-source.so"
pulseaudio_files += "${prefix}/lib/pulse-5.0/modules/libprotocol-esound.so"
pulseaudio_files += "${prefix}/lib/pulse-5.0/modules/module-esound-compat-spawnfd.so"
pulseaudio_files += "${prefix}/lib/pulse-5.0/modules/module-esound-compat-spawnpid.so"
pulseaudio_files += "${prefix}/lib/pulse-5.0/modules/module-esound-protocol-tcp.so"
pulseaudio_files += "${prefix}/lib/pulse-5.0/modules/module-esound-protocol-unix.so"
pulseaudio_files += "${prefix}/lib/pulse-5.0/modules/module-gconf.so"
pulseaudio_files += "${prefix}/lib/pulse-5.0/modules/module-udev-detect.so"
pulseaudio_files += "${prefix}/lib/pulse-5.0/modules/module-role-cork.so"
pulseaudio_files += "${prefix}/lib/pulse-5.0/modules/module-switch-on-port-available.so"
pulseaudio_files += "${prefix}/lib/pulse-5.0/modules/module-virtual-surround-sink.so"
pulseaudio_files += "${prefix}/lib/pulse-5.0/modules/module-role-ducking.so"
pulseaudio_files += "${prefix}/lib/pulse-5.0/modules/module-systemd-login.so"
pulseaudio_files += "${prefix}/lib/systemd/user/pulseaudio.service"
pulseaudio_files += "${prefix}/lib/systemd/user/pulseaudio.socket"
pulseaudio_files += "${prefix}/lib/pulse-5.0/modules/module-policy.so"
pulseaudio_files += "${prefix}/lib/pulse-5.0/modules/libvolume-api.so"
pulseaudio_files += "${prefix}/lib/pulse-5.0/modules/libmain-volume-policy.so"
pulseaudio_files += "${prefix}/lib/pulse-5.0/modules/module-volume-api.so"
pulseaudio_files += "${prefix}/lib/pulse-5.0/modules/module-main-volume-policy.so"
pulseaudio_files += "${prefix}/lib/pulse-5.0/modules/module-audio-groups.so"
pulseaudio_files += "/etc/bash_completion.d/pulseaudio-bash-completion.sh"
CONFFILES_${PN} = ""
CONFFILES_${PN} += "${sysconfdir}/pulse/filter/*.dat"
MANIFESTFILES_${PN} = "pulseaudio.manifest"

pulseaudio-module-dev_files = ""
pulseaudio-module-dev_files += "${prefix}/include/pulsemodule/pulsecore/*.h"
pulseaudio-module-dev_files += "${prefix}/include/pulsemodule/pulse/*.h"
pulseaudio-module-dev_files += "${prefix}/include/pulsemodule/modules/main-volume-policy/*.h"
pulseaudio-module-dev_files += "${prefix}/include/pulsemodule/modules/volume-api/*.h"
pulseaudio-module-dev_files += "${prefix}/lib/pkgconfig/pulseaudio-module-devel.pc"
MANIFESTFILES_${PN}-module-dev = "pulseaudio.manifest"

libpulse-dev_files = ""
libpulse-dev_files += "${prefix}/include/pulse/*"
libpulse-dev_files += "${prefix}/lib/libpulse.so"
libpulse-dev_files += "${prefix}/lib/libpulse-simple.so"
libpulse-dev_files += "${prefix}/lib/libpulse-mainloop-glib.so"
libpulse-dev_files += "${prefix}/lib/pkgconfig/libpulse*.pc"
libpulse-dev_files += "${prefix}/share/vala/vapi/libpulse.vapi"
libpulse-dev_files += "${prefix}/lib/cmake/PulseAudio/PulseAudioConfig.cmake"
libpulse-dev_files += "${prefix}/lib/cmake/PulseAudio/PulseAudioConfigVersion.cmake"
MANIFESTFILES_libpulse-dev = "pulseaudio.manifest"

pulseaudio-vala-bindings_files = ""
pulseaudio-vala-bindings_files += "${prefix}/share/vala/vapi/*"
MANIFESTFILES_${PN}-vala-bindings = "pulseaudio.manifest"

pulseaudio-module-switch-on-connect_files = ""
pulseaudio-module-switch-on-connect_files += "${prefix}/lib/pulse-5.0/modules/module-switch-on-connect.so"
MANIFESTFILES_${PN}-module-switch-on-connect = "pulseaudio.manifest"

pulseaudio-docs_files = ""

pulseaudio-module-null-source_files = ""
pulseaudio-module-null-source_files += "${prefix}/lib/pulse-5.0/modules/module-null-source.so"
MANIFESTFILES_${PN}-module-null-source = "pulseaudio.manifest"

FILES_${PN}-module-filter = "${pulseaudio-module-filter_files}"
FILES_libpulse = "${libpulse_files}"
FILES_${PN}-module-dbus-protocol = "${pulseaudio-module-dbus-protocol_files}"
FILES_${PN}-realtime-scheduling = "${pulseaudio-realtime-scheduling_files}"
FILES_${PN}-module-combine-sink = "${pulseaudio-module-combine-sink_files}"
FILES_${PN}-module-bluetooth = "${pulseaudio-module-bluetooth_files}"
FILES_${PN}-utils = "${pulseaudio-utils_files}"
FILES_${PN}-module-raop = "${pulseaudio-module-raop_files}"
FILES_${PN}-config = "${pulseaudio-config_files}"
FILES_libpulse-mainloop-glib = "${libpulse-mainloop-glib_files}"
FILES_${PN}-module-augment-properties = "${pulseaudio-module-augment-properties_files}"
FILES_${PN} = "${pulseaudio_files}"
FILES_${PN}-module-dev = "${pulseaudio-module-dev_files}"
FILES_libpulse-dev = "${libpulse-dev_files}"
FILES_${PN}-vala-bindings = "${pulseaudio-vala-bindings_files}"
FILES_${PN}-module-switch-on-connect = "${pulseaudio-module-switch-on-connect_files}"
FILES_${PN}-docs = "${pulseaudio-docs_files}"
FILES_${PN}-module-null-source = "${pulseaudio-module-null-source_files}"

PKG_pulseaudio-module-filter= "pulseaudio-module-filter"
PKG_libpulse= "libpulse"
PKG_pulseaudio-module-dbus-protocol= "pulseaudio-module-dbus-protocol"
PKG_pulseaudio-realtime-scheduling= "pulseaudio-realtime-scheduling"
PKG_pulseaudio-module-combine-sink= "pulseaudio-module-combine-sink"
PKG_pulseaudio-module-bluetooth= "pulseaudio-module-bluetooth"
PKG_pulseaudio-utils= "pulseaudio-utils"
PKG_pulseaudio-module-raop= "pulseaudio-module-raop"
PKG_pulseaudio-config= "pulseaudio-config"
PKG_libpulse-mainloop-glib= "libpulse-mainloop-glib"
PKG_pulseaudio-module-augment-properties= "pulseaudio-module-augment-properties"
PKG_pulseaudio= "pulseaudio"
PKG_pulseaudio-module-dev= "pulseaudio-module-dev"
PKG_libpulse-dev= "libpulse-dev"
PKG_pulseaudio-vala-bindings= "pulseaudio-vala-bindings"
PKG_pulseaudio-module-switch-on-connect= "pulseaudio-module-switch-on-connect"
PKG_pulseaudio-docs= "pulseaudio-docs"
PKG_pulseaudio-module-null-source= "pulseaudio-module-null-source"

require pulseaudio-extraconf.inc

