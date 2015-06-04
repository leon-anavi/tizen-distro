DESCRIPTION = "Test stub of testkit-lite"
HOMEPAGE = "http://nohomepage.org"
SECTION = "Development/Testing"
LICENSE = "GPL-2.0"
PV = "1.0"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

EXTRA_OEMAKE += "SYS_ROOT=${D}"
INHIBIT_PACKAGE_STRIP = "1"
INSANE_SKIP_${PN} = "arch"

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by testkit-stub


RDEPENDS = ""

DEPENDS = ""

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q -n testkit-stub-1.0
 cp ${S}/packaging/testkit-stub.manifest .
 
 
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
 
 oe_runmake ${PARALLEL_MAKE}
}

do_install() {
 export RPM_BUILD_ROOT=${D}
 cd ${S}
 LANG=C
 export LANG
 unset DISPLAY
 rm -rf ${D}
 mkdir -p ${D}
 
 rm -rf ${D}
 
   oe_runmake \
         DESTDIR=${D} \
         INSTALL_ROOT=${D} \
         BINDIR=${prefix}/bin \
   install  
   rm -f ${D}${infodir}/dir 
   find ${D} -regex ".*\.la$" | xargs rm -f -- 
   find ${D} -regex ".*\.a$" | xargs rm -f --
 
 
 
}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " testkit-stub "

testkit-stub_files = ""
testkit-stub_files += "${prefix}/bin/testkit-stub"
MANIFESTFILES_${PN} = "testkit-stub.manifest"

FILES_${PN} = "${testkit-stub_files}"

PKG_testkit-stub= "testkit-stub"

require testkit-stub-extraconf.inc

