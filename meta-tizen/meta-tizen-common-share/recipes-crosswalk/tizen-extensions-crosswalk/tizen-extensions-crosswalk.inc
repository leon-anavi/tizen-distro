DESCRIPTION = "Tizen Web APIs implemented using Crosswalk"
HOMEPAGE = "http://nohomepage.org"
SECTION = "Development/Libraries"
LICENSE = "BSD-3-Clause and Apache-2.0"
PV = "0.143"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by tizen-extensions-crosswalk-bluetooth-demo
PROVIDES += "tizen-extensions-crosswalk-bluetooth-demo"


#PROVIDES by tizen-extensions-crosswalk-audiosystem-demo
PROVIDES += "tizen-extensions-crosswalk-audiosystem-demo"


#PROVIDES by tizen-extensions-crosswalk


#PROVIDES by tizen-extensions-crosswalk-examples
PROVIDES += "tizen-extensions-crosswalk-examples"


#PROVIDES by tizen-extensions-crosswalk-system-info-demo
PROVIDES += "tizen-extensions-crosswalk-system-info-demo"


RDEPENDS = ""
#RDEPENDS of tizen-extensions-crosswalk-bluetooth-demo (${PN}-bluetooth-demo)
RDEPENDS_${PN}-bluetooth-demo += "tizen-extensions-crosswalk"

#RDEPENDS of tizen-extensions-crosswalk-audiosystem-demo (${PN}-audiosystem-demo)
RDEPENDS_${PN}-audiosystem-demo += "tizen-extensions-crosswalk"

#RDEPENDS of tizen-extensions-crosswalk (${PN})
RDEPENDS_${PN} += "crosswalk"
RDEPENDS_${PN} += "media-thumbnail-server"

#RDEPENDS of tizen-extensions-crosswalk-examples (${PN}-examples)
RDEPENDS_${PN}-examples += "tizen-extensions-crosswalk"

#RDEPENDS of tizen-extensions-crosswalk-system-info-demo (${PN}-system-info-demo)
RDEPENDS_${PN}-system-info-demo += "tizen-extensions-crosswalk"


DEPENDS = ""
#DEPENDS of tizen-extensions-crosswalk
DEPENDS += "capi-web-url-download"
DEPENDS += "capi-system-power"
DEPENDS += "pkgmgr"
DEPENDS += "capi-appfw-application"
DEPENDS += "libgsignon-glib"
DEPENDS += "app-core"
DEPENDS += "capi-network-bluetooth"
DEPENDS += "dbus-glib"
DEPENDS += "pkgmgr-info"
DEPENDS += "notification"
inherit pkgconfig
DEPENDS += "glib-2.0"
DEPENDS += "system-server"
DEPENDS += "wayland"
DEPENDS += "capi-system-runtime-info"
DEPENDS += "libtapi"
DEPENDS += "capi-web-favorites"
DEPENDS += "capi-appfw-app-manager"
inherit pythonnative
DEPENDS += "evas"
DEPENDS += "tizen-platform-config"
DEPENDS += "capi-network-nfc"
DEPENDS += "capi-system-system-settings"
DEPENDS += "udev"
DEPENDS += "capi-system-sensor"
DEPENDS_append_class-native = " ninja-native"
DEPENDS_append_class-target = " ninja-native"
DEPENDS += "vconf"
DEPENDS += "capi-appfw-package-manager"
DEPENDS += "capi-system-info"
DEPENDS += "capi-content-media-content"
DEPENDS += "pulseaudio"
DEPENDS += "bluez5"
DEPENDS += "capi-system-device"
DEPENDS += "capi-network-connection"
DEPENDS += "message-port"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 
 cp ${S}/packaging/tizen-extensions-crosswalk.manifest .
 cp ${S}/packaging/tizen-extensions-crosswalk.png .
 cp ${S}/packaging/tizen-extensions-crosswalk-bluetooth-demo .
 cp ${S}/packaging/tizen-extensions-crosswalk-examples .
 cp ${S}/packaging/tizen-extensions-crosswalk-system-info-demo .
 
 
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
 
 
 export GYP_GENERATORS='ninja'
 GYP_OPTIONS="--depth=. -Dtizen=1 -Dextension_build_type=Release -Dextension_host_os=ivi -Ddisplay_type=wayland"
 
 ./tools/gyp/gyp $GYP_OPTIONS tizen-wrt.gyp
 
 ninja -C out/Default -j16
 
 
 
}

do_install() {
 export RPM_BUILD_ROOT=${D}
 cd ${S}
 LANG=C
 export LANG
 unset DISPLAY
 rm -rf ${D}
 mkdir -p ${D}
 
 
 # Binary wrapper.
 install -m 755 -D ${S}/packaging/tizen-extensions-crosswalk-bluetooth-demo ${D}${prefix}/bin/tizen-extensions-crosswalk-bluetooth-demo
 install -m 755 -D ${S}/packaging/tizen-extensions-crosswalk-examples ${D}${prefix}/bin/tizen-extensions-crosswalk-examples
 install -m 755 -D ${S}/packaging/tizen-extensions-crosswalk-system-info-demo ${D}${prefix}/bin/tizen-extensions-crosswalk-system-info-demo
 install -m 755 -D ${S}/packaging/tizen-extensions-crosswalk-audiosystem-demo ${D}${prefix}/bin/tizen-extensions-crosswalk-audiosystem-demo
 
 # Extensions.
 mkdir -p ${D}${prefix}/lib/tizen-extensions-crosswalk
 install -p -m 644 out/Default/libtizen*.so ${D}${prefix}/lib/tizen-extensions-crosswalk
 
 # Examples.
 mkdir -p ${D}${prefix}/share/tizen-extensions-crosswalk/examples
 mkdir -p ${D}${prefix}/share/tizen-extensions-crosswalk/examples/js
 install -p -m 644 examples/*.html ${D}${prefix}/share/tizen-extensions-crosswalk/examples
 install -p -m 644 examples/js/*.js ${D}${prefix}/share/tizen-extensions-crosswalk/examples/js
 
 # Demos
 mkdir -p ${D}${prefix}/share/tizen-extensions-crosswalk/demos/tizen
 mkdir -p ${D}${prefix}/share/tizen-extensions-crosswalk/demos/tizen/css
 mkdir -p ${D}${prefix}/share/tizen-extensions-crosswalk/demos/tizen/js
 mkdir -p ${D}${prefix}/share/tizen-extensions-crosswalk/demos/tizen/images
 
 install -p -m 644 demos/tizen/*.html ${D}${prefix}/share/tizen-extensions-crosswalk/demos/tizen
 install -p -m 644 demos/tizen/css/*.css ${D}${prefix}/share/tizen-extensions-crosswalk/demos/tizen/css
 install -p -m 644 demos/tizen/js/*.js ${D}${prefix}/share/tizen-extensions-crosswalk/demos/tizen/js
 install -p -m 644 demos/tizen/images/*.png ${D}${prefix}/share/tizen-extensions-crosswalk/demos/tizen/images
 
 # Demos - System Info
 mkdir -p ${D}${prefix}/share/tizen-extensions-crosswalk/demos/system_info
 mkdir -p ${D}${prefix}/share/tizen-extensions-crosswalk/demos/system_info/css
 mkdir -p ${D}${prefix}/share/tizen-extensions-crosswalk/demos/system_info/js
 mkdir -p ${D}${prefix}/share/tizen-extensions-crosswalk/demos/system_info/images
 
 install -p -m 644 demos/system_info/*.html ${D}${prefix}/share/tizen-extensions-crosswalk/demos/system_info
 install -p -m 644 demos/system_info/css/*.css ${D}${prefix}/share/tizen-extensions-crosswalk/demos/system_info/css
 install -p -m 644 demos/system_info/js/*.js ${D}${prefix}/share/tizen-extensions-crosswalk/demos/system_info/js
 install -p -m 644 demos/system_info/images/*.png ${D}${prefix}/share/tizen-extensions-crosswalk/demos/system_info/images
 
 # Demos - audiosystem api 
 mkdir -p ${D}${prefix}/share/tizen-extensions-crosswalk/demos/audiosystem
 mkdir -p ${D}${prefix}/share/tizen-extensions-crosswalk/demos/audiosystem/css
 mkdir -p ${D}${prefix}/share/tizen-extensions-crosswalk/demos/audiosystem/css/ui-lightness
 mkdir -p ${D}${prefix}/share/tizen-extensions-crosswalk/demos/audiosystem/css/ui-lightness/images
 mkdir -p ${D}${prefix}/share/tizen-extensions-crosswalk/demos/audiosystem/js
 mkdir -p ${D}${prefix}/share/tizen-extensions-crosswalk/demos/audiosystem/images
 
 install -p -m 644 demos/audiosystem/*.html ${D}${prefix}/share/tizen-extensions-crosswalk/demos/audiosystem
 install -p -m 644 demos/audiosystem/css/*.css ${D}${prefix}/share/tizen-extensions-crosswalk/demos/audiosystem/css
 install -p -m 644 demos/audiosystem/css/ui-lightness/*.css ${D}${prefix}/share/tizen-extensions-crosswalk/demos/audiosystem/css/ui-lightness
 install -p -m 644 demos/audiosystem/css/ui-lightness/images/* ${D}${prefix}/share/tizen-extensions-crosswalk/demos/audiosystem/css/ui-lightness/images
 install -p -m 644 demos/audiosystem/js/*.js ${D}${prefix}/share/tizen-extensions-crosswalk/demos/audiosystem/js
 install -p -m 644 demos/audiosystem/images/*.png ${D}${prefix}/share/tizen-extensions-crosswalk/demos/audiosystem/images
 
 # register to the package manager
 install -m 644 -D tizen-extensions-crosswalk-examples.xml ${D}${prefix}/share/packages/tizen-extensions-crosswalk-examples.xml
 install -m 644 -D tizen-extensions-crosswalk-bluetooth-demo.xml ${D}${prefix}/share/packages/tizen-extensions-crosswalk-bluetooth-demo.xml
 install -m 644 -D tizen-extensions-crosswalk-system-info-demo.xml ${D}${prefix}/share/packages/tizen-extensions-crosswalk-system-info-demo.xml
 install -m 644 -D tizen-extensions-crosswalk-audiosystem-demo.xml ${D}${prefix}/share/packages/tizen-extensions-crosswalk-audiosystem-demo.xml
 install -p -D tizen-extensions-crosswalk.png ${D}${prefix}/share/icons/default/small/tizen-extensions-crosswalk-examples.png
 install -p -D tizen-extensions-crosswalk.png ${D}${prefix}/share/icons/default/small/tizen-extensions-crosswalk-bluetooth-demo.png
 install -p -D tizen-extensions-crosswalk.png ${D}${prefix}/share/icons/default/small/tizen-extensions-crosswalk-system-info-demo.png
 install -p -D tizen-extensions-crosswalk.png ${D}${prefix}/share/icons/default/small/tizen-extensions-crosswalk-audiosystem-demo.png
 
 
}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " tizen-extensions-crosswalk-bluetooth-demo "
PACKAGES += " tizen-extensions-crosswalk-audiosystem-demo "
PACKAGES += " tizen-extensions-crosswalk "
PACKAGES += " tizen-extensions-crosswalk-examples "
PACKAGES += " tizen-extensions-crosswalk-system-info-demo "

tizen-extensions-crosswalk-bluetooth-demo_files = ""
tizen-extensions-crosswalk-bluetooth-demo_files += "${prefix}/bin/tizen-extensions-crosswalk-bluetooth-demo"
tizen-extensions-crosswalk-bluetooth-demo_files += "${prefix}/share/packages/tizen-extensions-crosswalk-bluetooth-demo.xml"
tizen-extensions-crosswalk-bluetooth-demo_files += "${prefix}/share/icons/default/small/tizen-extensions-crosswalk-bluetooth-demo.png"
tizen-extensions-crosswalk-bluetooth-demo_files += "${prefix}/share/tizen-extensions-crosswalk/demos/tizen/*.html"
tizen-extensions-crosswalk-bluetooth-demo_files += "${prefix}/share/tizen-extensions-crosswalk/demos/tizen/css/*.css"
tizen-extensions-crosswalk-bluetooth-demo_files += "${prefix}/share/tizen-extensions-crosswalk/demos/tizen/js/*.js"
tizen-extensions-crosswalk-bluetooth-demo_files += "${prefix}/share/tizen-extensions-crosswalk/demos/tizen/images/*.png"

tizen-extensions-crosswalk-audiosystem-demo_files = ""
tizen-extensions-crosswalk-audiosystem-demo_files += "${prefix}/bin/tizen-extensions-crosswalk-audiosystem-demo"
tizen-extensions-crosswalk-audiosystem-demo_files += "${prefix}/share/packages/tizen-extensions-crosswalk-audiosystem-demo.xml"
tizen-extensions-crosswalk-audiosystem-demo_files += "${prefix}/share/icons/default/small/tizen-extensions-crosswalk-audiosystem-demo.png"
tizen-extensions-crosswalk-audiosystem-demo_files += "${prefix}/share/tizen-extensions-crosswalk/demos/audiosystem/index.html"
tizen-extensions-crosswalk-audiosystem-demo_files += "${prefix}/share/tizen-extensions-crosswalk/demos/audiosystem/css/*.css"
tizen-extensions-crosswalk-audiosystem-demo_files += "${prefix}/share/tizen-extensions-crosswalk/demos/audiosystem/css/ui-lightness/*.css"
tizen-extensions-crosswalk-audiosystem-demo_files += "${prefix}/share/tizen-extensions-crosswalk/demos/audiosystem/css/ui-lightness/images/*"
tizen-extensions-crosswalk-audiosystem-demo_files += "${prefix}/share/tizen-extensions-crosswalk/demos/audiosystem/js/*.js"
tizen-extensions-crosswalk-audiosystem-demo_files += "${prefix}/share/tizen-extensions-crosswalk/demos/audiosystem/images/*"

tizen-extensions-crosswalk_files = ""
tizen-extensions-crosswalk_files += "${prefix}/lib/tizen-extensions-crosswalk/libtizen*.so"

tizen-extensions-crosswalk-examples_files = ""
tizen-extensions-crosswalk-examples_files += "${prefix}/bin/tizen-extensions-crosswalk-examples"
tizen-extensions-crosswalk-examples_files += "${prefix}/share/packages/tizen-extensions-crosswalk-examples.xml"
tizen-extensions-crosswalk-examples_files += "${prefix}/share/icons/default/small/tizen-extensions-crosswalk-examples.png"
tizen-extensions-crosswalk-examples_files += "${prefix}/share/tizen-extensions-crosswalk/examples/*.html"
tizen-extensions-crosswalk-examples_files += "${prefix}/share/tizen-extensions-crosswalk/examples/js/*.js"

tizen-extensions-crosswalk-system-info-demo_files = ""
tizen-extensions-crosswalk-system-info-demo_files += "${prefix}/bin/tizen-extensions-crosswalk-system-info-demo"
tizen-extensions-crosswalk-system-info-demo_files += "${prefix}/share/packages/tizen-extensions-crosswalk-system-info-demo.xml"
tizen-extensions-crosswalk-system-info-demo_files += "${prefix}/share/icons/default/small/tizen-extensions-crosswalk-system-info-demo.png"
tizen-extensions-crosswalk-system-info-demo_files += "${prefix}/share/tizen-extensions-crosswalk/demos/system_info/*.html"
tizen-extensions-crosswalk-system-info-demo_files += "${prefix}/share/tizen-extensions-crosswalk/demos/system_info/css/*.css"
tizen-extensions-crosswalk-system-info-demo_files += "${prefix}/share/tizen-extensions-crosswalk/demos/system_info/js/*.js"
tizen-extensions-crosswalk-system-info-demo_files += "${prefix}/share/tizen-extensions-crosswalk/demos/system_info/images/*.png"

FILES_${PN}-bluetooth-demo = "${tizen-extensions-crosswalk-bluetooth-demo_files}"
FILES_${PN}-audiosystem-demo = "${tizen-extensions-crosswalk-audiosystem-demo_files}"
FILES_${PN} = "${tizen-extensions-crosswalk_files}"
FILES_${PN}-examples = "${tizen-extensions-crosswalk-examples_files}"
FILES_${PN}-system-info-demo = "${tizen-extensions-crosswalk-system-info-demo_files}"

PKG_tizen-extensions-crosswalk-bluetooth-demo= "tizen-extensions-crosswalk-bluetooth-demo"
PKG_tizen-extensions-crosswalk-audiosystem-demo= "tizen-extensions-crosswalk-audiosystem-demo"
PKG_tizen-extensions-crosswalk= "tizen-extensions-crosswalk"
PKG_tizen-extensions-crosswalk-examples= "tizen-extensions-crosswalk-examples"
PKG_tizen-extensions-crosswalk-system-info-demo= "tizen-extensions-crosswalk-system-info-demo"

require tizen-extensions-crosswalk-extraconf.inc

