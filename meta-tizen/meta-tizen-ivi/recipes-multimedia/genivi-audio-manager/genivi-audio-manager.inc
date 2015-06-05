DESCRIPTION = "GENIVI Audio Manager"
HOMEPAGE = "http://nohomepage.org"
SECTION = "Automotive/API"
LICENSE = "MPL-2.0"
PV = "6.0"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by genivi-audio-manager-dev
PROVIDES += "genivi-audio-manager-dev"


#PROVIDES by genivi-audio-manager


RDEPENDS = ""
#RDEPENDS of genivi-audio-manager-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "genivi-audio-manager"

#RDEPENDS of genivi-audio-manager (${PN})
RDEPENDS_${PN} += "glibc"


DEPENDS = ""
#DEPENDS of genivi-audio-manager
DEPENDS += "flex"
DEPENDS += "systemd"
DEPENDS += "dlt-daemon"
inherit tizen_cmake
inherit pythonnative
DEPENDS += "dbus"
DEPENDS += "zlib"
inherit pkgconfig
DEPENDS += "CommonAPI"
DEPENDS_append_class-native = " bison-native"
DEPENDS_append_class-target = " bison-native"
DEPENDS += "sqlite3"
DEPENDS += "CommonAPI-DBus"
DEPENDS += "murphy"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q -n genivi-audio-manager-6.0
 cp ${S}/packaging/genivi-audio-manager.manifest .
 
 
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
 
 mkdir -p build
 cd build
 
 
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
         ${EXTRA_OECMAKE} -DUSE_BUILD_LIBS=OFF \
        -DWITH_TESTS=OFF \
        -DWITH_ENABLED_IPC=DBUS \
        -DWITH_DBUS_WRAPPER=ON \
        -DWITH_NSM=OFF \
        -DWITH_DLT=OFF \
        -DCMAKE_INSTALL_PREFIX=${prefix} \
        ..
 #make VERBOSE=1
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
 
 rm -rf "${D}"
 cd build
 
   oe_runmake \
         DESTDIR=${D} \
         INSTALL_ROOT=${D} \
         BINDIR=${prefix}/bin \
   install  
   rm -f ${D}${infodir}/dir 
   find ${D} -regex ".*\.la$" | xargs rm -f -- 
   find ${D} -regex ".*\.a$" | xargs rm -f --
 mkdir -p ${D}${prefix}/include/genivi-audio-manager
 for cpath in *.h command control routing shared; do
     mv ${D}${prefix}/include/${cpath} ${D}${prefix}/include/genivi-audio-manager
 done
 rm ${D}${prefix}/lib/audioManager/routing/libPluginRoutingInterfaceAsync.so*
 
 
}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " genivi-audio-manager-dev "
PACKAGES += " genivi-audio-manager "

genivi-audio-manager-dev_files = ""
genivi-audio-manager-dev_files += "${prefix}/include/genivi-audio-manager/*"
MANIFESTFILES_${PN}-dev = "genivi-audio-manager.manifest"

genivi-audio-manager_files = ""
genivi-audio-manager_files += "LICENCE README.html"
genivi-audio-manager_files += "${prefix}/bin/AudioManager"
genivi-audio-manager_files += "${prefix}/bin/domain-manager"
genivi-audio-manager_files += "${prefix}/lib/audioManager/command/libPluginCommandInterfaceDbus.so*"
genivi-audio-manager_files += "${prefix}/lib/audioManager/routing/libPluginRoutingInterfaceDbus.so*"
genivi-audio-manager_files += "${prefix}/lib/audioManager/control/libPluginControlInterface.so*"
genivi-audio-manager_files += "${prefix}/lib/audioManager/control/libPluginControlInterfaceDbus.so*"
genivi-audio-manager_files += "${prefix}/lib/audioManager/control/libPluginControlInterfaceMurphy.so*"
genivi-audio-manager_files += "${prefix}/share/audiomanager/*xml"
MANIFESTFILES_${PN} = "genivi-audio-manager.manifest"

FILES_${PN}-dev = "${genivi-audio-manager-dev_files}"
FILES_${PN} = "${genivi-audio-manager_files}"

PKG_genivi-audio-manager-dev= "genivi-audio-manager-dev"
PKG_genivi-audio-manager= "genivi-audio-manager"

require genivi-audio-manager-extraconf.inc

