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

#PROVIDES by crosswalk-thirdparty
# the PROVIDES rules is ignore "crosswalk-thirdparty  "


RDEPENDS = ""
#RDEPENDS of crosswalk-thirdparty (${PN})
RDEPENDS_${PN} += "ca-certificates-tizen"
RDEPENDS_${PN} += "ss-server"


DEPENDS = ""
#DEPENDS of crosswalk-thirdparty
DEPENDS += "cairo"
DEPENDS += "expat"
DEPENDS += "udev"
DEPENDS += "libxslt"
DEPENDS += "glib-2.0"
DEPENDS += "bzip2"
DEPENDS += "nss"
DEPENDS += "alsa-lib"
DEPENDS += "elfutils"
inherit pkgconfig
DEPENDS += "yasm"
inherit perlnative
DEPENDS += "wayland"
DEPENDS += "which"
DEPENDS += "libxml2"
DEPENDS += "libcap"
DEPENDS += "flex"
DEPENDS += "gperf"
inherit pythonnative
DEPENDS += "python-xml"
DEPENDS_append_class-native = " ninja-native"
DEPENDS_append_class-target = " ninja-native"
DEPENDS += "pango"
DEPENDS += "vconf"
DEPENDS += "fontconfig"
DEPENDS += "libxkbcommon"
DEPENDS += "dbus"
DEPENDS += "pulseaudio"
DEPENDS_append_class-native = " bison-native"
DEPENDS_append_class-target = " bison-native"
DEPENDS += "pciutils"
DEPENDS += "binutils"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q -n crosswalk
 
 cp ${S}/packaging/crosswalk-thirdparty.manifest .
 cp ${S}/packaging/xwalk-thirdparty.gyp src/xwalk/
 
 
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
 
 
 
 # Stop unconditionally passing -Wall to the compiler. Chromium has its own
 # mechanisms for deciding which parts of the code need -Wall and which need it
 # to be left out (since several pieces are built with -Werror). At least in
 # M39, this is preventing the "rtc_base" target from being built because it
 # does not expect -Wall to be passed to the compiler (see webrtc issue 3307).
 export CXXFLAGS="`echo $CXXFLAGS | sed s,-Wall,,g`"
 
 # Do not use -finline-functions: it breaks the build because it causes -Wall to
 # warn about some conditions that cannot really be reached (ie. variables that
 # may be used uninitialized while in fact thay cannot be uninitialized). See
 # TC-2299.
 export CXXFLAGS="`echo $CXXFLAGS | sed s,-finline-functions,,g`"
 
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
 ./src/xwalk/gyp_xwalk src/xwalk/xwalk-thirdparty.gyp \
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
 -Duse_system_yasm=1 \
 -Denable_hidpi=1 \
 -Dwerror= \
 -Dskia_warnings_as_errors=0
 
 ninja -j16 -C src/out/Release xwalk-thirdparty
 
 
 
}

do_install() {
 export RPM_BUILD_ROOT=${D}
 cd ${S}
 LANG=C
 export LANG
 unset DISPLAY
 rm -rf ${D}
 mkdir -p ${D}
 
 
 
 mkdir  -p ${D}${prefix}/share/crosswalk-thirdparty/
 tar -zcvf out.tgz src/out
 cp -ar out.tgz ${D}${prefix}/share/crosswalk-thirdparty/
 
 
}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " crosswalk-thirdparty "

crosswalk-thirdparty_files = ""
crosswalk-thirdparty_files += "${prefix}/share/crosswalk-thirdparty/*"
MANIFESTFILES_${PN} = "crosswalk-thirdparty.manifest"

FILES_${PN} = "${crosswalk-thirdparty_files}"

PKG_crosswalk-thirdparty= "crosswalk-thirdparty"

require crosswalk-thirdparty-extraconf.inc

