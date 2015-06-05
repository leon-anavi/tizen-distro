DESCRIPTION = "Automotive Message Broker is a vehicle network abstraction system"
HOMEPAGE = "http://nohomepage.org"
SECTION = "Automotive/ICO Homescreen"
LICENSE = "LGPL-2.1"
PV = "0.9.5"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by ico-vic-amb-plugin


RDEPENDS = ""
#RDEPENDS of ico-vic-amb-plugin (${PN})
RDEPENDS_${PN} += "ico-uxf-utilities"
RDEPENDS_${PN} += "glibc"


DEPENDS = ""
#DEPENDS of ico-vic-amb-plugin
DEPENDS += "ico-uxf-utilities"
inherit tizen_cmake
DEPENDS += "json-c"
inherit pkgconfig
DEPENDS += "app-core"
DEPENDS += "sed"
DEPENDS += "automotive-message-broker"
DEPENDS += "elementary"
DEPENDS += "boost"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q -n ico-vic-amb-plugin-0.9.5
 cp ${S}/packaging/ico-vic-amb-plugin.manifest .
 sed -i 's#LIBDIR#${prefix}/lib/#' packaging.in/config.tizen-ico
 
 
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
         ${EXTRA_OECMAKE}
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
 mkdir -p ${D}${sysconfdir}/ambd/examples/
 cp src/AMBformat.conf ${D}/${sysconfdir}/ambd/
 cp packaging.in/config.tizen-ico ${D}${sysconfdir}/ambd/examples/config.tizen-ico
 mkdir -p ${D}${prefix}/bin
 cp tool/ico_set_vehicleinfo ${D}${prefix}/bin/ico_set_vehicleinfo
 
 
}

pkg_postinst_${PN}() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
    # When installing ($1 == 1)
    if [ $1 -eq 1 ] ; then
      # Back up the original configuration and create a symlink
      # to ours if the configuration file exists.
      if [ -f "$D${sysconfdir}/ambd/config.tizen" ]; then
        echo "moving original AMB config.tizen -> config.tizen.orig"
        mv "$D${sysconfdir}/ambd/config.tizen" "$D${sysconfdir}/ambd/config.tizen.orig"
        echo "creating symlink AMB config.tizen -> examples/config.tizen-ico"
        ln -sf "$D${sysconfdir}/ambd/examples/config.tizen-ico" "$D${sysconfdir}/ambd/config.tizen"
      fi
    fi
    /bin/systemctl restart ambd

}

pkg_postrm_${PN}() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
    # When uninstalling ($1 == 0)
    if [ $1 -eq 0 ] ; then
      # Return the original file if a symlink exists and
      # we have the backup around
      if [ -L "$D${sysconfdir}/ambd/config.tizen" ]; then
        if [ -f "$D${sysconfdir}/ambd/config.tizen.orig" ]; then
          echo "restoring AMB config file config.tizen.orig as config.tizen"
          mv "$D${sysconfdir}/ambd/config.tizen.orig" "$D${sysconfdir}/ambd/config.tizen"
        fi
      fi
    fi
    /bin/systemctl restart ambd

}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " ico-vic-amb-plugin "

ico-vic-amb-plugin_files = ""
ico-vic-amb-plugin_files += "${prefix}/lib/automotive-message-broker/*.so"
ico-vic-amb-plugin_files += "${sysconfdir}/ambd/AMBformat.conf"
ico-vic-amb-plugin_files += "${sysconfdir}/ambd/examples/config.tizen-ico"
ico-vic-amb-plugin_files += "${prefix}/share/doc/automotive-message-broker/ico-vic-amb-plugin/README"
ico-vic-amb-plugin_files += "${prefix}/bin/ico_set_vehicleinfo"
CONFFILES_${PN} = ""
CONFFILES_${PN} += "${sysconfdir}/ambd/AMBformat.conf"
CONFFILES_${PN} += "${sysconfdir}/ambd/examples/config.tizen-ico"
MANIFESTFILES_${PN} = "ico-vic-amb-plugin.manifest"

FILES_${PN} = "${ico-vic-amb-plugin_files}"

PKG_ico-vic-amb-plugin= "ico-vic-amb-plugin"

require ico-vic-amb-plugin-extraconf.inc

