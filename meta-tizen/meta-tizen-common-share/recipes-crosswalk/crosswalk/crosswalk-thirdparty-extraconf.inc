inherit gettext

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

DEPENDS += "yasm-native"

do_compile_prepend() {

 CC_host="gcc"; export CC_host
 CXX_host="g++"; export CXX_host

 LD="${CXX}" export LD
 CC="${CC}" export CC
 CXX="${CXX}" export CXX
 GYP_EXTRA_FLAGS="${GYP_EXTRA_FLAGS} -I${WORKDIR}/oe-defaults.gypi -I${WORKDIR}/include.gypi"
 GYP_EXTRA_FLAGS="${GYP_EXTRA_FLAGS} -Dhost_clang=0 "
}

do_configure() {
}
