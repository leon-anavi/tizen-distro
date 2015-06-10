DESCRIPTION = "Automotive Message Broker is a vehicle network abstraction system"
HOMEPAGE = "http://nohomepage.org"
SECTION = "Automotive/Service"
LICENSE = "LGPL-2.1"
PV = "0.13"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by automotive-message-broker-plugins-bluetooth
PROVIDES += "automotive-message-broker-plugins-bluetooth"


#PROVIDES by automotive-message-broker-plugins
PROVIDES += "automotive-message-broker-plugins"


#PROVIDES by automotive-message-broker-plugins-bluemonkey
PROVIDES += "automotive-message-broker-plugins-bluemonkey"


#PROVIDES by automotive-message-broker-plugins-qtmainloop
PROVIDES += "automotive-message-broker-plugins-qtmainloop"


#PROVIDES by automotive-message-broker-plugins-murphy
PROVIDES += "automotive-message-broker-plugins-murphy"


#PROVIDES by automotive-message-broker-plugins-cangen
PROVIDES += "automotive-message-broker-plugins-cangen"


#PROVIDES by automotive-message-broker-plugins-opencvlux
PROVIDES += "automotive-message-broker-plugins-opencvlux"


#PROVIDES by automotive-message-broker-plugins-test
PROVIDES += "automotive-message-broker-plugins-test"


#PROVIDES by automotive-message-broker-doc
PROVIDES += "automotive-message-broker-doc"


#PROVIDES by automotive-message-broker-plugins-wheel
PROVIDES += "automotive-message-broker-plugins-wheel"


#PROVIDES by automotive-message-broker-plugins-cansim
PROVIDES += "automotive-message-broker-plugins-cansim"


#PROVIDES by automotive-message-broker-plugins-common
PROVIDES += "automotive-message-broker-plugins-common"


#PROVIDES by automotive-message-broker-dev
PROVIDES += "automotive-message-broker-dev"


#PROVIDES by automotive-message-broker


#PROVIDES by automotive-message-broker-plugins-database
PROVIDES += "automotive-message-broker-plugins-database"


#PROVIDES by automotive-message-broker-plugins-websocket
PROVIDES += "automotive-message-broker-plugins-websocket"


#PROVIDES by automotive-message-broker-plugins-obd2
PROVIDES += "automotive-message-broker-plugins-obd2"


#PROVIDES by automotive-message-broker-xwalk-vehicle-extension
PROVIDES += "automotive-message-broker-xwalk-vehicle-extension"


#PROVIDES by automotive-message-broker-plugins-gpsnmea
PROVIDES += "automotive-message-broker-plugins-gpsnmea"


#PROVIDES by bluemonkey-modules-db
PROVIDES += "bluemonkey-modules-db"


RDEPENDS = ""
#RDEPENDS of automotive-message-broker-plugins-bluetooth (${PN}-plugins-bluetooth)
RDEPENDS_${PN}-plugins-bluetooth += "automotive-message-broker"

#RDEPENDS of automotive-message-broker-plugins (${PN}-plugins)
RDEPENDS_${PN}-plugins += "automotive-message-broker"

#RDEPENDS of automotive-message-broker-plugins-bluemonkey (${PN}-plugins-bluemonkey)
RDEPENDS_${PN}-plugins-bluemonkey += "automotive-message-broker-plugins-qtmainloop"
RDEPENDS_${PN}-plugins-bluemonkey += "automotive-message-broker"
RDEPENDS_${PN}-plugins-bluemonkey += "qt5-qtdeclarative"

#RDEPENDS of automotive-message-broker-plugins-qtmainloop (${PN}-plugins-qtmainloop)
RDEPENDS_${PN}-plugins-qtmainloop += "automotive-message-broker"
RDEPENDS_${PN}-plugins-qtmainloop += "qt5-qtcore"

#RDEPENDS of automotive-message-broker-plugins-murphy (${PN}-plugins-murphy)
RDEPENDS_${PN}-plugins-murphy += "murphy"
RDEPENDS_${PN}-plugins-murphy += "automotive-message-broker"

#RDEPENDS of automotive-message-broker-plugins-cangen (${PN}-plugins-cangen)
RDEPENDS_${PN}-plugins-cangen += "automotive-message-broker"

#RDEPENDS of automotive-message-broker-plugins-opencvlux (${PN}-plugins-opencvlux)
RDEPENDS_${PN}-plugins-opencvlux += "opencv"
RDEPENDS_${PN}-plugins-opencvlux += "automotive-message-broker"

#RDEPENDS of automotive-message-broker-plugins-test (${PN}-plugins-test)
RDEPENDS_${PN}-plugins-test += "automotive-message-broker"

#RDEPENDS of automotive-message-broker-doc (${PN}-doc)
RDEPENDS_${PN}-doc += "automotive-message-broker"

#RDEPENDS of automotive-message-broker-plugins-wheel (${PN}-plugins-wheel)
RDEPENDS_${PN}-plugins-wheel += "automotive-message-broker"

#RDEPENDS of automotive-message-broker-plugins-cansim (${PN}-plugins-cansim)
RDEPENDS_${PN}-plugins-cansim += "automotive-message-broker"

#RDEPENDS of automotive-message-broker-plugins-common (${PN}-plugins-common)
RDEPENDS_${PN}-plugins-common += "automotive-message-broker"

#RDEPENDS of automotive-message-broker-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "boost"
RDEPENDS_${PN}-dev += "util-linux"
RDEPENDS_${PN}-dev += "automotive-message-broker"

#RDEPENDS of automotive-message-broker (${PN})
RDEPENDS_${PN} += "automotive-message-broker-plugins"
RDEPENDS_${PN} += "python-pygobject"
RDEPENDS_${PN} += "default-ac-domains"
RDEPENDS_${PN} += "automotive-message-broker-plugins-murphy"
RDEPENDS_${PN} += "python-curses"
RDEPENDS_${PN} += "dbus-python"
RDEPENDS_${PN} += "glibc"

#RDEPENDS of automotive-message-broker-plugins-database (${PN}-plugins-database)
RDEPENDS_${PN}-plugins-database += "sqlite3"
RDEPENDS_${PN}-plugins-database += "automotive-message-broker"

#RDEPENDS of automotive-message-broker-plugins-websocket (${PN}-plugins-websocket)
RDEPENDS_${PN}-plugins-websocket += "libwebsockets"
RDEPENDS_${PN}-plugins-websocket += "automotive-message-broker"
RDEPENDS_${PN}-plugins-websocket += "qt5-qtcore"

#RDEPENDS of automotive-message-broker-plugins-obd2 (${PN}-plugins-obd2)
RDEPENDS_${PN}-plugins-obd2 += "automotive-message-broker-plugins-common"
RDEPENDS_${PN}-plugins-obd2 += "automotive-message-broker"

#RDEPENDS of automotive-message-broker-xwalk-vehicle-extension (${PN}-xwalk-vehicle-extension)
RDEPENDS_${PN}-xwalk-vehicle-extension += "crosswalk"
RDEPENDS_${PN}-xwalk-vehicle-extension += "automotive-message-broker"

#RDEPENDS of automotive-message-broker-plugins-gpsnmea (${PN}-plugins-gpsnmea)
RDEPENDS_${PN}-plugins-gpsnmea += "automotive-message-broker"

#RDEPENDS of bluemonkey-modules-db (bluemonkey-modules-db)
RDEPENDS_bluemonkey-modules-db += "qt5-plugin-sqldriver-sqlite"
RDEPENDS_bluemonkey-modules-db += "automotive-message-broker"


DEPENDS = ""
#DEPENDS of automotive-message-broker
DEPENDS += "qt5-plugin-bearer-nm"
DEPENDS += "qt5-plugin-bearer-connman"
inherit tizen_cmake
DEPENDS += "qt5-qtnetwork-dev"
DEPENDS += "qt5-qtdbus-dev"
DEPENDS += "opencv"
DEPENDS += "json-c"
DEPENDS += "dbus"
DEPENDS += "murphy"
inherit pkgconfig
DEPENDS += "glib-2.0"
DEPENDS += "sqlite3"
DEPENDS += "qt5-qtcore-dev"
DEPENDS_append_class-native = " libtool"
DEPENDS_append_class-target = " libtool-cross"
DEPENDS += "qt5-plugin-bearer-generic"
DEPENDS += "libwebsockets"
DEPENDS += "qt5-plugin-sqldriver-sqlite"
DEPENDS += "qt5-qtdeclarative-dev"
DEPENDS += "util-linux"
DEPENDS += "boost"
DEPENDS += "qt5-qtconcurrent-dev"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q -n automotive-message-broker-0.13
 
 
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
 
 
   cmake \
         -DCMAKE_VERBOSE_MAKEFILE=ON \
         -DCMAKE_INSTALL_PREFIX:PATH=${prefix} \
         -DCMAKE_INSTALL_LIBDIR:PATH=${prefix}/lib \
         -DINCLUDE_INSTALL_DIR:PATH=${prefix}/include \
         -DLIB_INSTALL_DIR:PATH=${prefix}/lib \
         -DSYSCONF_INSTALL_DIR:PATH=${sysconfdir} \
         -DSHARE_INSTALL_PREFIX:PATH=${prefix}/share \
         -DCMAKE_SKIP_RPATH:BOOL=ON \
         -DBUILD_SHARED_LIBS:BOOL=ON \
         -DCMAKE_TOOLCHAIN_FILE=${WORKDIR}/toolchain.cmake \
         ${EXTRA_OECMAKE} \
 	   -Dxwalk_vehicle_extension=ON \
 	   -DXWALK_EXTENSION_PATH=/tizen-extensions-crosswalk \
 	   -Dqtmainloop=ON \
 	   -Dopencvlux_plugin=ON \
 	   -Dwebsocket_plugin=ON \
 	   -Dbluetooth_plugin=ON \
 	   -Dbluemonkey_plugin=ON \
 	   -Ddatabase_plugin=ON \
 	   -Dmurphy_plugin=ON \
 	   -Dobd2_plugin=ON \
 	   -Dtest_plugin=ON \
 	   -Dgpsnmea_plugin=ON \
 	   -Dcangen_plugin=ON \
 	   -Dcansim_plugin=ON \
 	   -Dusebluez5=ON \
 	   -Denable_docs=ON
 
 
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
 
 mkdir -p ${D}${systemd_unitdir}/system/network.target.wants
 cp packaging.in/ambd.service.systemd.tizen ${D}${systemd_unitdir}/system/ambd.service
 ln -s ../ambd.service ${D}${systemd_unitdir}/system/network.target.wants/ambd.service
 
 mkdir -p ${D}/${systemd_unitdir}/system/multi-user.target.wants 
 ln -s ../ambd.service  ${D}/${systemd_unitdir}/system/multi-user.target.wants/ambd.service  
 
 cp packaging/config.tizen ${D}${sysconfdir}/ambd/
 
 
}

pkg_postinst_${PN}() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postinst_${PN}() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_${PN}() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_${PN}() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " automotive-message-broker-plugins-bluetooth "
PACKAGES += " automotive-message-broker-plugins-cangen "
PACKAGES += " automotive-message-broker-plugins-common "
PACKAGES += " automotive-message-broker-plugins-qtmainloop "
PACKAGES += " automotive-message-broker-plugins-murphy "
PACKAGES += " automotive-message-broker-plugins "
PACKAGES += " automotive-message-broker-plugins-opencvlux "
PACKAGES += " automotive-message-broker-plugins-test "
PACKAGES += " automotive-message-broker-plugins-wheel "
PACKAGES += " automotive-message-broker-plugins-cansim "
PACKAGES += " automotive-message-broker-plugins-bluemonkey "
PACKAGES += " automotive-message-broker-xwalk-vehicle-extension "
PACKAGES += " automotive-message-broker "
PACKAGES += " automotive-message-broker-plugins-database "
PACKAGES += " automotive-message-broker-plugins-websocket "
PACKAGES += " automotive-message-broker-plugins-obd2 "
PACKAGES += " automotive-message-broker-dev "
PACKAGES += " automotive-message-broker-plugins-gpsnmea "
PACKAGES += " bluemonkey-modules-db "

automotive-message-broker-plugins-bluetooth_files = ""
automotive-message-broker-plugins-bluetooth_files += "${prefix}/lib/automotive-message-broker/bluetoothplugin.so"
automotive-message-broker-plugins-bluetooth_files += "${sysconfdir}/dbus-1/system.d/ambbt.conf"
CONFFILES_${PN}-plugins-bluetooth = ""
CONFFILES_${PN}-plugins-bluetooth += "${sysconfdir}/dbus-1/system.d/ambbt.conf"
MANIFESTFILES_${PN}-plugins-bluetooth = "packaging.in/amb.manifest.plugins"

automotive-message-broker-plugins-cangen_files = ""
automotive-message-broker-plugins-cangen_files += "${prefix}/lib/automotive-message-broker/cangenplugin.so"
automotive-message-broker-plugins-cangen_files += "${prefix}/bin/gen-set"
MANIFESTFILES_${PN}-plugins-cangen = "packaging.in/amb.manifest.plugins"

automotive-message-broker-plugins-common_files = ""
automotive-message-broker-plugins-common_files += "${prefix}/lib/libamb-plugins-common.so"
MANIFESTFILES_${PN}-plugins-common = "packaging.in/amb.manifest.plugins"

automotive-message-broker-plugins-qtmainloop_files = ""
automotive-message-broker-plugins-qtmainloop_files += "${prefix}/lib/automotive-message-broker/qtmainloopplugin.so"
MANIFESTFILES_${PN}-plugins-qtmainloop = "packaging.in/amb.manifest.plugins"

automotive-message-broker-plugins-murphy_files = ""
automotive-message-broker-plugins-murphy_files += "${prefix}/lib/automotive-message-broker/murphysourceplugin.so"
MANIFESTFILES_${PN}-plugins-murphy = "packaging.in/amb.manifest.plugins"

automotive-message-broker-plugins_files = ""
automotive-message-broker-plugins_files += "${prefix}/lib/automotive-message-broker/examplesourceplugin.so"
automotive-message-broker-plugins_files += "${prefix}/lib/automotive-message-broker/examplesinkplugin.so"
automotive-message-broker-plugins_files += "${prefix}/lib/automotive-message-broker/dbussinkplugin.so"
automotive-message-broker-plugins_files += "${prefix}/lib/automotive-message-broker/demosinkplugin.so"
automotive-message-broker-plugins_files += "${sysconfdir}/dbus-1/system.d/amb.conf"
CONFFILES_${PN}-plugins = ""
CONFFILES_${PN}-plugins += "${sysconfdir}/dbus-1/system.d/amb.conf"
MANIFESTFILES_${PN}-plugins = "packaging.in/amb.manifest.plugins"

automotive-message-broker-plugins-opencvlux_files = ""
automotive-message-broker-plugins-opencvlux_files += "${prefix}/lib/automotive-message-broker/opencvluxplugin.so"
MANIFESTFILES_${PN}-plugins-opencvlux = "packaging.in/amb.manifest.plugins"

automotive-message-broker-plugins-test_files = ""
automotive-message-broker-plugins-test_files += "${prefix}/lib/automotive-message-broker/testplugin.so"
MANIFESTFILES_${PN}-plugins-test = "packaging.in/amb.manifest.plugins"

automotive-message-broker-doc_files = ""
automotive-message-broker-doc_files += "${prefix}/share/doc/packages/automotive-message-broker/*"
MANIFESTFILES_${PN}-doc = "packaging.in/amb.manifest.plugins"

automotive-message-broker-plugins-wheel_files = ""
automotive-message-broker-plugins-wheel_files += "${prefix}/lib/automotive-message-broker/wheelsourceplugin.so"
MANIFESTFILES_${PN}-plugins-wheel = "packaging.in/amb.manifest.plugins"

automotive-message-broker-plugins-cansim_files = ""
automotive-message-broker-plugins-cansim_files += "${prefix}/lib/automotive-message-broker/cansimplugin.so"
MANIFESTFILES_${PN}-plugins-cansim = "packaging.in/amb.manifest.plugins"

automotive-message-broker-plugins-bluemonkey_files = ""
automotive-message-broker-plugins-bluemonkey_files += "${prefix}/lib/automotive-message-broker/bluemonkeyplugin.so"
automotive-message-broker-plugins-bluemonkey_files += "${sysconfdir}/ambd/bluemonkey"
CONFFILES_${PN}-plugins-bluemonkey = ""
CONFFILES_${PN}-plugins-bluemonkey += "${sysconfdir}/ambd/bluemonkey"
MANIFESTFILES_${PN}-plugins-bluemonkey = "packaging.in/amb.manifest.plugins"

automotive-message-broker-xwalk-vehicle-extension_files = ""
automotive-message-broker-xwalk-vehicle-extension_files += "${prefix}/lib/tizen-extensions-crosswalk/*"
automotive-message-broker-xwalk-vehicle-extension_files += "${prefix}/share/automotive-message-broker/xwalk/examples/*"
MANIFESTFILES_${PN}-xwalk-vehicle-extension = "packaging.in/amb.manifest.plugins"

automotive-message-broker_files = ""
automotive-message-broker_files += "${sysconfdir}/ambd/config"
automotive-message-broker_files += "${sysconfdir}/ambd/config.tizen"
automotive-message-broker_files += "${sysconfdir}/ambd/examples/*"
automotive-message-broker_files += "${prefix}/bin/ambd"
automotive-message-broker_files += "${prefix}/lib/libamb.so*"
automotive-message-broker_files += "${systemd_unitdir}/system/ambd.service"
automotive-message-broker_files += "${systemd_unitdir}/system/network.target.wants/ambd.service"
automotive-message-broker_files += "${systemd_unitdir}/system/multi-user.target.wants/ambd.service"
automotive-message-broker_files += "${prefix}/bin/amb-get"
automotive-message-broker_files += "${prefix}/bin/amb-get-history"
automotive-message-broker_files += "${prefix}/bin/amb-set"
automotive-message-broker_files += "${prefix}/bin/amb-listen"
automotive-message-broker_files += "${prefix}/bin/ambctl"
CONFFILES_${PN} = ""
CONFFILES_${PN} += "${sysconfdir}/ambd/config"
CONFFILES_${PN} += "${sysconfdir}/ambd/config.tizen"
CONFFILES_${PN} += "${sysconfdir}/ambd/examples/*"
MANIFESTFILES_${PN} = "packaging.in/amb.manifest"

automotive-message-broker-plugins-database_files = ""
automotive-message-broker-plugins-database_files += "${prefix}/lib/automotive-message-broker/databasesinkplugin.so"
MANIFESTFILES_${PN}-plugins-database = "packaging.in/amb.manifest.plugins"

automotive-message-broker-plugins-websocket_files = ""
automotive-message-broker-plugins-websocket_files += "${prefix}/lib/automotive-message-broker/websocketsource.so"
automotive-message-broker-plugins-websocket_files += "${prefix}/lib/automotive-message-broker/websocketsink.so"
MANIFESTFILES_${PN}-plugins-websocket = "packaging.in/amb.manifest.plugins"

automotive-message-broker-plugins-obd2_files = ""
automotive-message-broker-plugins-obd2_files += "${prefix}/lib/automotive-message-broker/obd2sourceplugin.so"
MANIFESTFILES_${PN}-plugins-obd2 = "packaging.in/amb.manifest.plugins"

automotive-message-broker-dev_files = ""
automotive-message-broker-dev_files += "${prefix}/include/amb/*.h"
automotive-message-broker-dev_files += "${prefix}/include/amb/*.hpp"
automotive-message-broker-dev_files += "${prefix}/lib/pkgconfig/*.pc"
MANIFESTFILES_${PN}-dev = "packaging.in/amb.manifest.plugins"

automotive-message-broker-plugins-gpsnmea_files = ""
automotive-message-broker-plugins-gpsnmea_files += "${prefix}/lib/automotive-message-broker/gpsnmea.so"
MANIFESTFILES_${PN}-plugins-gpsnmea = "packaging.in/amb.manifest.plugins"

bluemonkey-modules-db_files = ""
bluemonkey-modules-db_files += "${prefix}/lib/automotive-message-broker/bluemonkeyDbModule.so"
MANIFESTFILES_bluemonkey-modules-db = "packaging.in/amb.manifest.plugins"

FILES_${PN}-plugins-bluetooth = "${automotive-message-broker-plugins-bluetooth_files}"
FILES_${PN}-plugins-cangen = "${automotive-message-broker-plugins-cangen_files}"
FILES_${PN}-plugins-common = "${automotive-message-broker-plugins-common_files}"
FILES_${PN}-plugins-qtmainloop = "${automotive-message-broker-plugins-qtmainloop_files}"
FILES_${PN}-plugins-murphy = "${automotive-message-broker-plugins-murphy_files}"
FILES_${PN}-plugins = "${automotive-message-broker-plugins_files}"
FILES_${PN}-plugins-opencvlux = "${automotive-message-broker-plugins-opencvlux_files}"
FILES_${PN}-plugins-test = "${automotive-message-broker-plugins-test_files}"
FILES_${PN}-doc = "${automotive-message-broker-doc_files}"
FILES_${PN}-plugins-wheel = "${automotive-message-broker-plugins-wheel_files}"
FILES_${PN}-plugins-cansim = "${automotive-message-broker-plugins-cansim_files}"
FILES_${PN}-plugins-bluemonkey = "${automotive-message-broker-plugins-bluemonkey_files}"
FILES_${PN}-xwalk-vehicle-extension = "${automotive-message-broker-xwalk-vehicle-extension_files}"
FILES_${PN} = "${automotive-message-broker_files}"
FILES_${PN}-plugins-database = "${automotive-message-broker-plugins-database_files}"
FILES_${PN}-plugins-websocket = "${automotive-message-broker-plugins-websocket_files}"
FILES_${PN}-plugins-obd2 = "${automotive-message-broker-plugins-obd2_files}"
FILES_${PN}-dev = "${automotive-message-broker-dev_files}"
FILES_${PN}-plugins-gpsnmea = "${automotive-message-broker-plugins-gpsnmea_files}"
FILES_bluemonkey-modules-db = "${bluemonkey-modules-db_files}"

PKG_automotive-message-broker-plugins-bluetooth= "automotive-message-broker-plugins-bluetooth"
PKG_automotive-message-broker-plugins-cangen= "automotive-message-broker-plugins-cangen"
PKG_automotive-message-broker-plugins-common= "automotive-message-broker-plugins-common"
PKG_automotive-message-broker-plugins-qtmainloop= "automotive-message-broker-plugins-qtmainloop"
PKG_automotive-message-broker-plugins-murphy= "automotive-message-broker-plugins-murphy"
PKG_automotive-message-broker-plugins= "automotive-message-broker-plugins"
PKG_automotive-message-broker-plugins-opencvlux= "automotive-message-broker-plugins-opencvlux"
PKG_automotive-message-broker-plugins-test= "automotive-message-broker-plugins-test"
PKG_automotive-message-broker-doc= "automotive-message-broker-doc"
PKG_automotive-message-broker-plugins-wheel= "automotive-message-broker-plugins-wheel"
PKG_automotive-message-broker-plugins-cansim= "automotive-message-broker-plugins-cansim"
PKG_automotive-message-broker-plugins-bluemonkey= "automotive-message-broker-plugins-bluemonkey"
PKG_automotive-message-broker-xwalk-vehicle-extension= "automotive-message-broker-xwalk-vehicle-extension"
PKG_automotive-message-broker= "automotive-message-broker"
PKG_automotive-message-broker-plugins-database= "automotive-message-broker-plugins-database"
PKG_automotive-message-broker-plugins-websocket= "automotive-message-broker-plugins-websocket"
PKG_automotive-message-broker-plugins-obd2= "automotive-message-broker-plugins-obd2"
PKG_automotive-message-broker-dev= "automotive-message-broker-dev"
PKG_automotive-message-broker-plugins-gpsnmea= "automotive-message-broker-plugins-gpsnmea"
PKG_bluemonkey-modules-db= "bluemonkey-modules-db"

require automotive-message-broker-extraconf.inc

