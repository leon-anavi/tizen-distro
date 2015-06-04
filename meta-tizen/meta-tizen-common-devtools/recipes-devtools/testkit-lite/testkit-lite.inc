DESCRIPTION = "Test runner with a command-line interface"
HOMEPAGE = "http://nohomepage.org"
SECTION = "Development/Testing"
LICENSE = "GPL-2.0"
PV = "3.1.7"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by testkit-lite


RDEPENDS = ""
#RDEPENDS of testkit-lite (${PN})
RDEPENDS_${PN} += "python"
RDEPENDS_${PN} += "testkit-stub"
RDEPENDS_${PN} += "python-lxml"
RDEPENDS_${PN} += "python-requests"
RDEPENDS_${PN} += "dbus-python"
RDEPENDS_${PN} += "python-ctypes"
RDEPENDS_${PN} += "python-pip"


DEPENDS = ""
#DEPENDS of testkit-lite
inherit pythonnative
DEPENDS_append_class-native = " fdupes-native"
DEPENDS_append_class-target = " fdupes-native"
DEPENDS += "python-requests"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/testkit-lite.manifest .
 # for rpmlint warning: remove shebang from python library
 sed -i '/^#!/d' ./testkitlite/commodule/androidmobile.py
 sed -i '/^#!/d' ./testkitlite/commodule/localhost.py
 sed -i '/^#!/d' ./testkitlite/commodule/tizenivi.py
 sed -i '/^#!/d' ./testkitlite/commodule/tizenlocal.py
 sed -i '/^#!/d' ./testkitlite/commodule/tizenmobile.py
 sed -i '/^#!/d' ./testkitlite/engines/androidunit.py
 sed -i '/^#!/d' ./testkitlite/engines/default.py
 sed -i '/^#!/d' ./testkitlite/engines/pyunit.py
 sed -i '/^#!/d' ./testkitlite/util/autoexec.py
 sed -i '/^#!/d' ./testkitlite/util/config.py
 sed -i '/^#!/d' ./testkitlite/util/connector.py
 sed -i '/^#!/d' ./testkitlite/util/errors.py
 sed -i '/^#!/d' ./testkitlite/util/httprequest.py
 sed -i '/^#!/d' ./testkitlite/util/killall.py
 sed -i '/^#!/d' ./testkitlite/util/log.py
 sed -i '/^#!/d' ./testkitlite/util/process.py
 sed -i '/^#!/d' ./testkitlite/util/result.py
 sed -i '/^#!/d' ./testkitlite/util/session.py
 sed -i '/^#!/d' ./testkitlite/util/str2.py
 sed -i '/^#!/d' ./testkitmerge/merger.py
 
 
 
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
 
 #empty
 
 
 
}

do_install() {
 export RPM_BUILD_ROOT=${D}
 cd ${S}
 LANG=C
 export LANG
 unset DISPLAY
 rm -rf ${D}
 mkdir -p ${D}
 
 python setup.py install --prefix=${prefix} --root=${D}
 install -d ${D}${prefix}/share/testkit-lite
 cp -r xsd ${D}${prefix}/share/testkit-lite
 #fdupes ${D}
 CURDIR=$(pwd)
 cd  ${D}${prefix}/lib/python2.7/site-packages
 
 find . -name '*.pyc' -exec rm -f {} \; 
 python -c "import sys, os, compileall; br='${D}'; compileall.compile_dir(sys.argv[1], ddir=br and (sys.argv[1][len(os.path.abspath(br)):]+'/') or None)" . 
 cd ${CURDIR}
 
 
 
}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " testkit-lite "

testkit-lite_files = ""
testkit-lite_files += "${sysconfdir}/dbus-1/system.d/com.intel.testkit.conf"
testkit-lite_files += "${prefix}/bin/testkit-lite"
testkit-lite_files += "${prefix}/bin/testkit-lite-dbus"
testkit-lite_files += "${prefix}/bin/testkit-merge"
testkit-lite_files += "/opt/testkit/lite/mh.html"
testkit-lite_files += "/opt/testkit/lite/testkit-lite_user_guide.pdf"
testkit-lite_files += "/opt/testkit/lite/testkit-lite_tutorial.pdf"
testkit-lite_files += "/opt/testkit/lite/test_definition_schema.pdf"
testkit-lite_files += "${prefix}/lib/python2.7/site-packages/testkitlite/*"
testkit-lite_files += "${prefix}/lib/python2.7/site-packages/testkitmerge/*"
testkit-lite_files += "${prefix}/lib/python2.7/site-packages/testkit_lite-3.1.7-py2.7.egg-info/*"
testkit-lite_files += "${prefix}/share/testkit-lite"
testkit-lite_files += "/opt/testkit/lite/VERSION"
testkit-lite_files += "/opt/testkit/lite/commodule/CONFIG"
CONFFILES_${PN} = ""
CONFFILES_${PN} += "${sysconfdir}/dbus-1/system.d/com.intel.testkit.conf"
MANIFESTFILES_${PN} = "testkit-lite.manifest"

FILES_${PN} = "${testkit-lite_files}"

PKG_testkit-lite= "testkit-lite"

require testkit-lite-extraconf.inc

