DESCRIPTION = "Multimedia suite for Tizen Common"
HOMEPAGE = "http://nohomepage.org"
SECTION = "Development/Testing"
LICENSE = "GPL-2.0"
PV = "1.0.0"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by common-multimedia-suite


#PROVIDES by ivi-multimedia-tests
PROVIDES += "ivi-multimedia-tests"


#PROVIDES by gst-auto-launch
PROVIDES += "gst-auto-launch"


RDEPENDS = ""
#RDEPENDS of gst-auto-launch (gst-auto-launch)
RDEPENDS_gst-auto-launch += "gstreamer-utils"

#RDEPENDS of ivi-multimedia-tests (ivi-multimedia-tests)
RDEPENDS_ivi-multimedia-tests += "gstreamer-utils"
RDEPENDS_ivi-multimedia-tests += "testkit-lite"
RDEPENDS_ivi-multimedia-tests += "pulseaudio-utils"

#RDEPENDS of common-multimedia-suite (${PN})
RDEPENDS_${PN} += "common-suite-launcher"
RDEPENDS_${PN} += "testkit-lite"


DEPENDS = ""
#DEPENDS of common-multimedia-suite
DEPENDS += "glib-2.0"
inherit pkgconfig
DEPENDS += "gstreamer1.0"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/common-multimedia-suite.manifest .
 
 
 
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
EXTRA_OECONF += " --prefix=${prefix}"

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
 
 # common-multimedia-suite package 
 install -d ${D}${prefix}/share/tests/common-multimedia-suite
 install -m 0755 common/runtest.sh ${D}${prefix}/share/tests/common-multimedia-suite
 install -m 0644 common/*.xml ${D}${prefix}/share/tests/common-multimedia-suite
 install -m 0644 LICENSE ${D}${prefix}/share/tests/common-multimedia-suite
 cp -r common/TESTDIR ${D}${prefix}/share/tests/common-multimedia-suite
 
 # ivi-multimedia-tests package
 install -d ${D}${prefix}/share/tests/ivi-multimedia-tests/tts-gstreamer-tests
 install -d ${D}${prefix}/share/tests/ivi-multimedia-tests/tts-pulseaudio-tests
 install -m 0755 ivi/tts-gstreamer-tests/src/* ${D}${prefix}/share/tests/ivi-multimedia-tests/tts-gstreamer-tests
 install -m 0644 ivi/tts-gstreamer-tests/tests.xml ${D}${prefix}/share/tests/ivi-multimedia-tests/tts-gstreamer-tests
 install -m 0644 ivi/tts-gstreamer-tests/README ${D}${prefix}/share/tests/ivi-multimedia-tests/tts-gstreamer-tests
 install -m 0755 ivi/tts-pulseaudio-tests/src/*.sh ${D}${prefix}/share/tests/ivi-multimedia-tests/tts-pulseaudio-tests
 install -m 0644 ivi/tts-pulseaudio-tests/tests.xml ${D}${prefix}/share/tests/ivi-multimedia-tests/tts-pulseaudio-tests
 install -m 0644 ivi/tts-pulseaudio-tests/README ${D}${prefix}/share/tests/ivi-multimedia-tests/tts-pulseaudio-tests
 install -m 0644 LICENSE ${D}${prefix}/share/tests/ivi-multimedia-tests
 
 
}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " gst-auto-launch "
PACKAGES += " ivi-multimedia-tests "
PACKAGES += " common-multimedia-suite "

gst-auto-launch_files = ""
gst-auto-launch_files += "${prefix}/bin/gst-auto-launch"
gst-auto-launch_files += "${prefix}/share/gst-auto-launch"

ivi-multimedia-tests_files = ""
ivi-multimedia-tests_files += "${prefix}/share/tests/ivi-multimedia-tests"

common-multimedia-suite_files = ""
common-multimedia-suite_files += "${prefix}/share/tests/common-multimedia-suite"
MANIFESTFILES_${PN} = "common-multimedia-suite.manifest"

FILES_gst-auto-launch = "${gst-auto-launch_files}"
FILES_ivi-multimedia-tests = "${ivi-multimedia-tests_files}"
FILES_${PN} = "${common-multimedia-suite_files}"

PKG_gst-auto-launch= "gst-auto-launch"
PKG_ivi-multimedia-tests= "ivi-multimedia-tests"
PKG_common-multimedia-suite= "common-multimedia-suite"

require common-multimedia-suite-extraconf.inc

