DESCRIPTION = "Bluetooth-tools"
HOMEPAGE = "http://nohomepage.org"
SECTION = "Network & Connectivity/Bluetooth"
LICENSE = "Apache-2.0"
PV = "0.2.35"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by bluetooth-tools-no-firmware
PROVIDES += "bluetooth-tools-no-firmware"


#PROVIDES by bluetooth-tools


RDEPENDS = ""
#RDEPENDS of bluetooth-tools-no-firmware (${PN}-no-firmware)
RDEPENDS_${PN}-no-firmware += "bluetooth-tools"
RDEPENDS_${PN}-no-firmware += "rfkill"

#RDEPENDS of bluetooth-tools (${PN})
RDEPENDS_${PN} += "tizen-platform-config-tools"


DEPENDS = ""
#DEPENDS of bluetooth-tools
inherit tizen_cmake

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 
 
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
 
 export CFLAGS="${CFLAGS} -fpie -fvisibility=hidden"
 export LDFLAGS="${LDFLAGS} -Wl,--rpath=/usr/lib -Wl,--as-needed -Wl,--unresolved-symbols=ignore-in-shared-libs -pie"
 
 
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
         ${EXTRA_OECMAKE} . -DCMAKE_INSTALL_PREFIX=${prefix}
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
 
 mkdir -p ${D}${sysconfdir}/rc.d/rc3.d
 mkdir -p ${D}${sysconfdir}/rc.d/rc5.d
 ln -s ${sysconfdir}/rc.d/init.d/bluetooth-address ${D}${sysconfdir}/rc.d/rc3.d/S60bluetooth-address
 ln -s ${sysconfdir}/rc.d/init.d/bluetooth-address ${D}${sysconfdir}/rc.d/rc5.d/S60bluetooth-address
 
 mkdir -p ${D}${systemd_unitdir}/system/multi-user.target.wants
 install -m 0644 ${S}/packaging/bluetooth-address.service ${D}${systemd_unitdir}/system
 ln -s ../bluetooth-address.service ${D}${systemd_unitdir}/system/multi-user.target.wants/bluetooth-address.service
 
 mkdir -p ${D}${prefix}/etc/bluetooth/
 install -m 0755 scripts/bt-dev-start.sh ${D}${prefix}/etc/bluetooth/bt-dev-start.sh
 install -m 0755 scripts/bt-dev-end.sh ${D}${prefix}/etc/bluetooth/bt-dev-end.sh
 
 
}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " bluetooth-tools-no-firmware "
PACKAGES += " bluetooth-tools "

bluetooth-tools-no-firmware_files = ""
bluetooth-tools-no-firmware_files += "${prefix}/etc/bluetooth/bt-dev-end.sh"
bluetooth-tools-no-firmware_files += "${prefix}/etc/bluetooth/bt-dev-start.sh"
MANIFESTFILES_${PN}-no-firmware = "bluetooth-tools.manifest"

bluetooth-tools_files = ""
bluetooth-tools_files += "${sysconfdir}/rc.d/init.d/bluetooth-address"
bluetooth-tools_files += "${sysconfdir}/rc.d/rc3.d/S60bluetooth-address"
bluetooth-tools_files += "${sysconfdir}/rc.d/rc5.d/S60bluetooth-address"
bluetooth-tools_files += "${prefix}/etc/bluetooth/bt-stack-up.sh"
bluetooth-tools_files += "${prefix}/etc/bluetooth/bt-stack-down.sh"
bluetooth-tools_files += "${prefix}/etc/bluetooth/bt-reset-env.sh"
bluetooth-tools_files += "${prefix}/etc/bluetooth/bt-edutm-on.sh"
bluetooth-tools_files += "${prefix}/etc/bluetooth/bt-edutm-dev-up.sh"
bluetooth-tools_files += "${prefix}/etc/bluetooth/bt-edutm-mode-on.sh"
bluetooth-tools_files += "${prefix}/etc/bluetooth/bt-edutm-off.sh"
bluetooth-tools_files += "${systemd_unitdir}/system/multi-user.target.wants/bluetooth-address.service"
bluetooth-tools_files += "${systemd_unitdir}/system/bluetooth-address.service"
MANIFESTFILES_${PN} = "bluetooth-tools.manifest"

FILES_${PN}-no-firmware = "${bluetooth-tools-no-firmware_files}"
FILES_${PN} = "${bluetooth-tools_files}"

PKG_bluetooth-tools-no-firmware= "bluetooth-tools-no-firmware"
PKG_bluetooth-tools= "bluetooth-tools"

require bluetooth-tools-extraconf.inc

