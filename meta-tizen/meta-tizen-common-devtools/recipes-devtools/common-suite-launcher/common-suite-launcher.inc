DESCRIPTION = "Launcher of Tizen Common test suites"
HOMEPAGE = "http://nohomepage.org"
SECTION = "Development/Testing"
LICENSE = "GPL-2.0"
PV = "2.1.0"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by common-suite-launcher


RDEPENDS = ""
#RDEPENDS of common-suite-launcher (${PN})
RDEPENDS_${PN} += "xmlstarlet"
RDEPENDS_${PN} += "python-argparse"
RDEPENDS_${PN} += "python-lxml"


DEPENDS = ""

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/common-suite-launcher.manifest .
 
 
 
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
 
 install -d ${D}${prefix}/bin
 install -m 0755 src/common-suite-launcher ${D}${prefix}/bin
 install -m 0755 src/result-format ${D}${prefix}/bin
 
 
 
}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " common-suite-launcher "

common-suite-launcher_files = ""
common-suite-launcher_files += "${prefix}/bin/common-suite-launcher"
common-suite-launcher_files += "${prefix}/bin/result-format"
MANIFESTFILES_${PN} = "common-suite-launcher.manifest"

FILES_${PN} = "${common-suite-launcher_files}"

PKG_common-suite-launcher= "common-suite-launcher"

require common-suite-launcher-extraconf.inc

