DESCRIPTION = "Sanity suite for Tizen Common"
HOMEPAGE = "http://nohomepage.org"
SECTION = "Development/Testing"
LICENSE = "GPL-2.0"
PV = "1.1"

SRC_URI = "file://0001-Disable-the-system-set-with-tests-for-zypper-and-SMA.patch"

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by common-sanity-suite


RDEPENDS = ""
#RDEPENDS of common-sanity-suite (${PN})
RDEPENDS_${PN} += "common-suite-launcher"
RDEPENDS_${PN} += "testkit-lite"


DEPENDS = ""

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/common-sanity-suite.manifest .
 
 
 
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
 
 
 
 
 
}

do_install() {
 export RPM_BUILD_ROOT=${D}
 cd ${S}
 LANG=C
 export LANG
 unset DISPLAY
 rm -rf ${D}
 mkdir -p ${D}
 
 ## common-sanity-suite
 install -d ${D}${prefix}/share/tests/common/common-sanity-suite
 install -m 0755 runtest ${D}${prefix}/share/tests/common/common-sanity-suite
 install -m 644 *.xml ${D}${prefix}/share/tests/common/common-sanity-suite
 install -m 0644 LICENSE ${D}${prefix}/share/tests/common/common-sanity-suite
 cp -r TESTDIR ${D}${prefix}/share/tests/common/common-sanity-suite
 
 
 
}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " common-sanity-suite "

common-sanity-suite_files = ""
common-sanity-suite_files += "${prefix}/share/tests/common/common-sanity-suite"
MANIFESTFILES_${PN} = "common-sanity-suite.manifest"

FILES_${PN} = "${common-sanity-suite_files}"

PKG_common-sanity-suite= "common-sanity-suite"

require common-sanity-suite-extraconf.inc

