inherit gettext

DEPENDS += "crosswalk-thirdparty"

FILESEXTRAPATHS_prepend := "${THISDIR}/crosswalk:"

SRC_URI += "\
            file://include.gypi \
            file://oe-defaults.gypi \
            "
SRC_URI += "file://fix-crosbuild.patch"
SRC_URI += "file://fix-egl-version.patch"

# This comes from the chromium recipe:
# http://layers.openembedded.org/layerindex/recipe/4969/
# It allows architecture specific configuration
COMPATIBLE_MACHINE = "(-)"
COMPATIBLE_MACHINE_i586 = "(.*)"
COMPATIBLE_MACHINE_x86-64 = "(.*)"
COMPATIBLE_MACHINE_armv6 = "(.*)"
COMPATIBLE_MACHINE_armv7a = "(.*)"
COMPATIBLE_MACHINE_romley-ivb = "(.*)"
COMPATIBLE_MACHINE_valleyisland-64 = "(.*)"

RDEPENDS_${PN} += "libpulsecommon"

do_compile_prepend() {

 CC_host="gcc"; export CC_host
 CXX_host="g++"; export CXX_host

 LD="${CXX}" export LD
 CC="${CC}" export CC
 CXX="${CXX}" export CXX
 GYP_EXTRA_FLAGS="${GYP_EXTRA_FLAGS} -I${WORKDIR}/oe-defaults.gypi -I${WORKDIR}/include.gypi"
 GYP_EXTRA_FLAGS="${GYP_EXTRA_FLAGS} -Dhost_clang=0 "
 
 mkdir -p src/out
 tar -zxvf ${STAGING_DIR_HOST}${prefix}/share/crosswalk-thirdparty/out.tgz
}

do_configure() {
}

crosswalk-dbg_files += "/usr/lib/xwalk/.debug"
crosswalk-dbg_files += "/usr/lib/xwalk/.debug/libffmpegsumo.so"
crosswalk-dbg_files += "/usr/lib/xwalk/.debug/xwalk"

FILES_${PN}-dbg += "${crosswalk-dbg_files}"

pkg_postinst_${PN}() {
    #!/bin/sh -e

    mkdir -p $D${prefix}/share/icons/default/small
    mkdir -p $D${prefix}/share/packages
    mkdir -p $D/etc/package-manager/backendlib
    mkdir -p $D/etc/package-manager/backend
    ln -sf ${prefix}/lib/xwalk/libxwalk_backend_lib.so $D/etc/package-manager/backendlib/libxpk.so
    ln -sf ${prefix}/lib/xwalk/libxwalk_backend_lib.so $D/etc/package-manager/backendlib/libwgt.so
    ln -sf ${prefix}/lib/xwalk/xwalk_backend $D/etc/package-manager/backend/xpk
    ln -sf ${prefix}/lib/xwalk/xwalk_backend $D/etc/package-manager/backend/wgt

}
