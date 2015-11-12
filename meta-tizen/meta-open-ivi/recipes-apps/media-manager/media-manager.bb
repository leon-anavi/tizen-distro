SUMMARY = "GENIVI Media Manager"
DESCRIPTION = "The purpose of a common Media Manager API is to provide to IVI \
applications a way to control basic playback of contents of connected CE \
devices. A single API enables a wider range of available devices and media \
without implementing separate solutions for each type of device."
SECTION = "OpenIVI" 
PR = "r0" 

LICENSE = "MPL-2.0"
LIC_FILES_CHKSUM = "file://LICENCE;md5=815ca599c9df247a0c7f619bab123dad \
                    file://src/main.cpp;endline=12;md5=117b573e85833eff1e3b3c595d1ce868"

DEPENDS = "glib-2.0 jansson CommonAPI CommonAPI-DBus"
RDEPENDS_${PN} = "rygel lightmediascanner dleyna-renderer dleyna-server"

SRCREV_media-manager = "45e08ce242a6006aaaefaeda236f51c984eaeeb1"
SRCREV_media-manager-interfaces = "f0510129f8ac4fa48e7164dbb81ae9d0a922b9c4"
SRCREV_FORMAT = "media-manager"
SRC_URI = "git://git.projects.genivi.org/media-manager.git;name=media-manager \
           git://git.projects.genivi.org/media-manager-interfaces.git;name=media-manager-interfaces;destsuffix=git/src/interfaces \
          "

S = "${WORKDIR}/git"

inherit pkgconfig tizen_cmake

mediamanager_file = ""
mediamanager_file += "${prefix}/etc/udev/rules.d/10-media-manager-usb-mount-rules.rules"

do_configure() {
 cd ${S}
 mkdir build
}

do_compile() {
 cd ${S}/build
 LANG=C; export LANG;
 unset DISPLAY
 LD_AS_NEEDED=1; export LD_AS_NEEDED;

 export LDFLAGS="${LDFLAGS} -Wl,--rpath=${prefix}/lib -Wl,--as-needed -Wl,--hash-style=both"

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
         ${EXTRA_OECMAKE} ..
 oe_runmake

}

do_install() {
# install -d ${D}${bindir}
# install -m 0755 cameracapture ${D}${bindir}
 export RPM_BUILD_ROOT=${D}/build
 cd ${S}/build
 LANG=C; export LANG;
 unset DISPLAY
 rm -rf ${D}
 mkdir -p ${D}

 oe_runmake install \
         NO_ARLIB=1 \
         DESTDIR=${D} \
         LIBDIR=${prefix}/lib \
         USRLIBDIR=${prefix}/lib \
         BINDIR=${prefix}/bin \
         SBINDIR=${prefix}/sbin

}
