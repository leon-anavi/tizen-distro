DESCRIPTION = "Chromium-based app runtime"
HOMEPAGE = "https://github.com/otcshare/crosswalk"
SECTION = "Web Framework/Web Run Time"
LICENSE = "(BSD-3-Clause and LGPL-2.1+)"
PV = "11.40.277.0"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by crosswalk


#PROVIDES by widget-manifest-parser
PROVIDES += "widget-manifest-parser"


#PROVIDES by widget-manifest-parser-dev
PROVIDES += "widget-manifest-parser-dev"


RDEPENDS = ""
#RDEPENDS of crosswalk (${PN})
RDEPENDS_${PN} += "ca-certificates-tizen"
RDEPENDS_${PN} += "ss-server"

#RDEPENDS of widget-manifest-parser (widget-manifest-parser)
RDEPENDS_widget-manifest-parser += "crosswalk"

#RDEPENDS of widget-manifest-parser-dev (widget-manifest-parser-dev)
RDEPENDS_widget-manifest-parser-dev += "crosswalk"
RDEPENDS_widget-manifest-parser-dev += "widget-manifest-parser"


DEPENDS = ""
#DEPENDS of crosswalk
DEPENDS += "cairo"
DEPENDS += "pkgmgr"
DEPENDS += "expat"
DEPENDS += "udev"
DEPENDS += "app-core"
DEPENDS += "xmlsec1"
DEPENDS += "libxslt"
inherit perlnative
DEPENDS += "secure-storage"
DEPENDS += "bzip2"
DEPENDS += "nss"
DEPENDS += "alsa-lib"
DEPENDS += "elfutils"
inherit pkgconfig
DEPENDS += "yasm"
DEPENDS += "fontconfig"
DEPENDS += "system-server"
DEPENDS += "wayland"
DEPENDS += "which"
DEPENDS += "libxml2"
DEPENDS_append_class-native = " bison-native"
DEPENDS_append_class-target = " bison-native"
DEPENDS += "sensor"
DEPENDS += "icu"
DEPENDS += "flex"
DEPENDS += "freetype"
DEPENDS += "gperf"
inherit pythonnative
DEPENDS += "tizen-platform-config"
DEPENDS += "pkgmgr-info"
DEPENDS += "glib-2.0"
DEPENDS += "libdrm"
DEPENDS += "libcap"
DEPENDS += "python-xml"
DEPENDS_append_class-native = " ninja-native"
DEPENDS_append_class-target = " ninja-native"
DEPENDS += "pango"
DEPENDS += "vconf"
DEPENDS += "virtual/egl"
DEPENDS += "libxkbcommon"
DEPENDS += "dbus"
DEPENDS += "pulseaudio"
DEPENDS += "libexif"
DEPENDS += "ail"
DEPENDS += "capi-location-manager"
DEPENDS += "pciutils"
DEPENDS += "binutils"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q -n crosswalk
 
 cp ${S}/packaging/xwalk.in .
 cp ${S}/packaging/xwalk.service.in .
 cp ${S}/packaging/crosswalk.manifest .
 cp ${S}/packaging/crosswalk.xml.in .
 cp ${S}/packaging/crosswalk.png .
 cp ${S}/packaging/changedate.py .
 sed "s/@VERSION@/11.40.277.0/g" crosswalk.xml.in > crosswalk.xml
 sed "s|@LIB_INSTALL_DIR@|${prefix}/lib|g" xwalk.in > xwalk
 sed "s|@LIB_INSTALL_DIR@|${prefix}/lib|g" xwalk.service.in > xwalk.service
 
 # Widget manifest parser devel
 cp src/xwalk/tizen/widget-manifest-parser/widget-manifest-parser.pc.in .
 sed "s|@VERSION@|11.40.277.0|g" widget-manifest-parser.pc.in > widget-manifest-parser.pc

 cp -a src/AUTHORS AUTHORS.chromium
 cp -a src/LICENSE LICENSE.chromium
 cp -a src/xwalk/LICENSE LICENSE.xwalk
 
 # The profiles using Wayland (and thus Ozone) do not need this patch.
 
 
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
 
 
 mkdir -p src/out
 if [ -f ${prefix}/share/crosswalk-thirdparty/out.tgz ]; then
 tar -zxvf ${prefix}/share/crosswalk-thirdparty/out.tgz
 fi
 python ./changedate.py
 
 # Stop unconditionally passing -Wall to the compiler. Chromium has its own
 # mechanisms for deciding which parts of the code need -Wall and which need it
 # to be left out (since several pieces are built with -Werror). At least in
 # M39, this is preventing the "rtc_base" target from being built because it
 # does not expect -Wall to be passed to the compiler (see webrtc issue 3307).
 export CXXFLAGS="`echo $CXXFLAGS | sed s,-Wall,,g`"
 
 # For ffmpeg on ia32. The original CFLAGS set by the gyp and config files in
 # src/third_party/ffmpeg already pass -O2 -fomit-frame-pointer, but Tizen's
 # CFLAGS end up appending -fno-omit-frame-pointer. See http://crbug.com/37246
 export CFLAGS="`echo $CFLAGS | sed s,-fno-omit-frame-pointer,,g`"
 
 
 # Building the RPM in the GBS chroot fails with errors such as
 #   /usr/lib/gcc/i586-tizen-linux/4.7/../../../../i586-tizen-linux/bin/ld:
 #       failed to set dynamic section sizes: Memory exhausted
 # For now, work around it by passing a GNU ld-specific flag that optimizes the
 # linker for memory usage.
 export LDFLAGS="${LDFLAGS} -Wl,--no-keep-memory"
 
 # Support building in a non-standard directory, possibly outside ${WORKDIR}.
 # Since the build root is erased every time a new build is performed, one way
 # to avoid losing the build directory is to specify a location outside the
 # build root to the BUILDDIR_NAME definition, such as "/var/tmp/xwalk-build"
 # (remember all paths are still inside the chroot):
 #    gbs build --define 'BUILDDIR_NAME /some/path'
 BUILDDIR_NAME=""
 if [ -n "${BUILDDIR_NAME}" ]; then
    mkdir -p "${BUILDDIR_NAME}"
    ln -s "${BUILDDIR_NAME}" src/out
 fi
 
 GYP_EXTRA_FLAGS="${GYP_EXTRA_FLAGS} -Duse_ozone=1"
 
 # Force gold binary from chroot ld.gold provided by binutils-gold
 GYP_EXTRA_FLAGS="${GYP_EXTRA_FLAGS} -Ddisable_nacl=1 -Dlinux_use_bundled_binutils=0 -Dlinux_use_bundled_gold=0 "
 
 # Linking fails when fatal ld warnings are enabled. See XWALK-1379.
 GYP_EXTRA_FLAGS="${GYP_EXTRA_FLAGS} -Ddisable_fatal_linker_warnings=1"
 
 # For building for arm in OBS, we need :
 # -> to unset sysroot value.
 # sysroot variable is automatically set for cross compilation to use arm-sysroot provided by Chromium project
 # sysroot usage is not needed, we need to use arm libraries from the virtualized environment.
 #

 GYP_EXTRA_FLAGS="${GYP_EXTRA_FLAGS} -Dsysroot= "

 # Crosswalk build fails if the fpu selected in the gcc option is different from neon in case of arm7 compilation
 # So force it.
 
 
 
 # --no-parallel is added because chroot does not mount a /dev/shm, this will
 # cause python multiprocessing.SemLock error.
 export GYP_GENERATORS='ninja'
 export GYP_DEFINES="$GYP_DEFINES arm_float_abi=hard"
 ./src/xwalk/gyp_xwalk src/xwalk/xwalk.gyp \
 --no-parallel \
 ${GYP_EXTRA_FLAGS} \
 -Dchromeos=0 \
 -Dclang=0 \
 -Dlinux_use_bundled_binutils=0 \
 -Dlinux_use_bundled_gold=0 \
 -Dlinux_use_gold_flags=1 \
 -Dtizen=1 \
 -Dpython_ver=2.7 \
 -Duse_aura=1 \
 -Duse_cups=0 \
 -Duse_gconf=0 \
 -Duse_gnome_keyring=0 \
 -Duse_kerberos=0 \
 -Duse_system_bzip2=1 \
 -Duse_system_libexif=1 \
 -Duse_system_libxml=1 \
 -Duse_system_nspr=1 \
 -Duse_system_yasm=1 \
 -Dshared_process_mode=1 \
 -Denable_hidpi=1 \
 -Dwerror= \
 -Dskia_warnings_as_errors=0
 
 ninja -j16 -C src/out/Release xwalk xwalk_launcher xwalk_application_tools widget-manifest-parser
 
 
 
}

do_install() {
 export RPM_BUILD_ROOT=${D}
 cd ${S}
 LANG=C
 export LANG
 unset DISPLAY
 rm -rf ${D}
 mkdir -p ${D}
 
 # Binaries.
 install -p -D ${S}/packaging/org.crosswalkproject.Runtime1.service ${D}/usr/share/dbus-1/services/org.crosswalkproject.Runtime1.service
 install -p -D xwalk.service ${D}/usr/lib/systemd/user/xwalk.service
 install -p -D src/out/Release/xwalk ${D}${prefix}/lib/xwalk/xwalk
 install -p -D src/out/Release/xwalkctl ${D}${prefix}/bin/xwalkctl
 install -p -D src/out/Release/xwalk-launcher ${D}${prefix}/bin/xwalk-launcher
 install -p -D src/out/Release/xwalk_backend ${D}${prefix}/lib/xwalk/xwalk_backend
 install -p -D src/out/Release/lib/libxwalk_backend_lib.so ${D}${prefix}/lib/xwalk/libxwalk_backend_lib.so
 
 # Supporting libraries and resources.
 install -p -D src/out/Release/icudtl.dat ${D}${prefix}/lib/xwalk/icudtl.dat
 install -p -D src/out/Release/libffmpegsumo.so ${D}${prefix}/lib/xwalk/libffmpegsumo.so
 install -p -D src/out/Release/xwalk.pak ${D}${prefix}/lib/xwalk/xwalk.pak
 mkdir -p ${D}${prefix}/share/xwalk
 install -p -D src/xwalk/application/common/tizen/configuration/*.xsd ${D}${prefix}/share/xwalk/
 
 # PNaCl
 
 # Register xwalk to the package manager.
 install -m 0644 -p -D crosswalk.xml ${D}${prefix}/share/packages/crosswalk.xml
 install -m 0644 -p -D crosswalk.png ${D}${prefix}/share/icons/default/small/crosswalk.png
 
 # Widget manifest parser devel
 install -m 0664 -p -D src/xwalk/tizen/widget-manifest-parser/widget-manifest-parser.h ${D}${prefix}/include/widget-manifest-parser/widget-manifest-parser.h
 install -m 0664 -p -D widget-manifest-parser.pc ${D}${prefix}/lib/pkgconfig/widget-manifest-parser.pc
 
 # Widget manifest parser
 install -m 0755 -p -D src/out/Release/lib/libwidget-manifest-parser.so ${D}${prefix}/lib/libwidget-manifest-parser.so
 
 
}

pkg_postinst_${PN}() {
    #!/bin/sh -e

    mkdir -p $D${prefix}/share/icons/default/small
    mkdir -p $D${prefix}/share/packages
    ln -sf $D${prefix}/lib/xwalk/libxwalk_backend_lib.so /etc/package-manager/backendlib/libxpk.so
    ln -sf $D${prefix}/lib/xwalk/libxwalk_backend_lib.so /etc/package-manager/backendlib/libwgt.so
    ln -sf $D${prefix}/lib/xwalk/xwalk_backend /etc/package-manager/backend/xpk
    ln -sf $D${prefix}/lib/xwalk/xwalk_backend /etc/package-manager/backend/wgt

}

pkg_prerm_${PN}() {
    #!/bin/sh -e

    if [ $1 -eq 0 ] ; then
     # don't remove if we are upgrade the rpm package
    [ -L /etc/package-manager/backendlib/libxpk.so ] && rm /etc/package-manager/backendlib/libxpk.so
    [ -L /etc/package-manager/backendlib/libwgt.so ] && rm /etc/package-manager/backendlib/libwgt.so
    [ -L /etc/package-manager/backend/xpk ] && rm /etc/package-manager/backend/xpk
    [ -L /etc/package-manager/backend/wgt ] && rm /etc/package-manager/backend/wgt
    fi

}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " crosswalk "
PACKAGES += " widget-manifest-parser "
PACKAGES += " widget-manifest-parser-dev "

crosswalk_files = ""
crosswalk_files += "${prefix}/bin/xwalkctl"
crosswalk_files += "${prefix}/bin/xwalk-launcher"
crosswalk_files += "${prefix}/lib/xwalk/icudtl.dat"
crosswalk_files += "${prefix}/lib/xwalk/libffmpegsumo.so"
crosswalk_files += "${prefix}/lib/xwalk/xwalk"
crosswalk_files += "${prefix}/lib/xwalk/xwalk.pak"
crosswalk_files += "${prefix}/lib/xwalk/libxwalk_backend_lib.so"
crosswalk_files += "${prefix}/lib/xwalk/xwalk_backend"
crosswalk_files += "${prefix}/share/packages/crosswalk.xml"
crosswalk_files += "${prefix}/share/icons/default/small/crosswalk.png"
crosswalk_files += "/usr/share/dbus-1/services/org.crosswalkproject.Runtime1.service"
crosswalk_files += "/usr/lib/systemd/user/xwalk.service"
crosswalk_files += "${prefix}/share/xwalk/*"
MANIFESTFILES_${PN} = "crosswalk.manifest"

widget-manifest-parser_files = ""
widget-manifest-parser_files += "${prefix}/lib/libwidget-manifest-parser.so"

widget-manifest-parser-dev_files = ""
widget-manifest-parser-dev_files += "${prefix}/include/widget-manifest-parser/widget-manifest-parser.h"
widget-manifest-parser-dev_files += "${prefix}/lib/pkgconfig/widget-manifest-parser.pc"

FILES_${PN} = "${crosswalk_files}"
FILES_widget-manifest-parser = "${widget-manifest-parser_files}"
FILES_widget-manifest-parser-dev = "${widget-manifest-parser-dev_files}"

PKG_crosswalk= "crosswalk"
PKG_widget-manifest-parser= "widget-manifest-parser"
PKG_widget-manifest-parser-dev= "widget-manifest-parser-dev"

require crosswalk-extraconf.inc

