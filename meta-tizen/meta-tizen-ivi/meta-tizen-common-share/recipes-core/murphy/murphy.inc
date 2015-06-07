DESCRIPTION = "Resource policy framework"
HOMEPAGE = "http://nohomepage.org"
SECTION = "System/Service"
LICENSE = "BSD-3-Clause"
PV = "0.0.67"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by murphy-dev
PROVIDES += "murphy-dev"


#PROVIDES by murphy-core
PROVIDES += "murphy-core"


#PROVIDES by murphy-ecore
PROVIDES += "murphy-ecore"


#PROVIDES by murphy-pulse
PROVIDES += "murphy-pulse"


#PROVIDES by murphy-doc
PROVIDES += "murphy-doc"


#PROVIDES by murphy


#PROVIDES by murphy-ivi-resource-manager
PROVIDES += "murphy-ivi-resource-manager"


#PROVIDES by murphy-glib-dev
PROVIDES += "murphy-glib-dev"


#PROVIDES by murphy-pulse-dev
PROVIDES += "murphy-pulse-dev"


#PROVIDES by murphy-tests
PROVIDES += "murphy-tests"


#PROVIDES by murphy-gam
PROVIDES += "murphy-gam"


#PROVIDES by murphy-system-controller
PROVIDES += "murphy-system-controller"
# the PROVIDES rules is ignore "system-controller  "
PROVIDES += "system-controller"
RPROVIDES_murphy-system-controller += "system-controller"


#PROVIDES by murphy-plugins-base
PROVIDES += "murphy-plugins-base"


#PROVIDES by murphy-glib
PROVIDES += "murphy-glib"


#PROVIDES by murphy-gam-dev
PROVIDES += "murphy-gam-dev"


#PROVIDES by murphy-ecore-dev
PROVIDES += "murphy-ecore-dev"


RDEPENDS = ""
#RDEPENDS of murphy-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "murphy-core"
RDEPENDS_${PN}-dev += "json-c"

#RDEPENDS of murphy-ecore (${PN}-ecore)
RDEPENDS_${PN}-ecore += "murphy-core"

#RDEPENDS of murphy-pulse (${PN}-pulse)
RDEPENDS_${PN}-pulse += "murphy-core"

#RDEPENDS of murphy (${PN})
RDEPENDS_${PN} += "murphy-core"
RDEPENDS_${PN} += "libcap"
RDEPENDS_${PN} += "/bin/systemctl"

#RDEPENDS of murphy-gam-dev (${PN}-gam-dev)
RDEPENDS_${PN}-gam-dev += "murphy-gam"

#RDEPENDS of murphy-pulse-dev (${PN}-pulse-dev)
RDEPENDS_${PN}-pulse-dev += "murphy-core"
RDEPENDS_${PN}-pulse-dev += "murphy-pulse"

#RDEPENDS of murphy-tests (${PN}-tests)
RDEPENDS_${PN}-tests += "murphy-core"
RDEPENDS_${PN}-tests += "murphy"

#RDEPENDS of murphy-gam (${PN}-gam)
RDEPENDS_${PN}-gam += "murphy"

#RDEPENDS of murphy-system-controller (${PN}-system-controller)
RDEPENDS_${PN}-system-controller += "ico-uxf-homescreen"

#RDEPENDS of murphy-plugins-base (${PN}-plugins-base)
RDEPENDS_${PN}-plugins-base += "murphy-core"
RDEPENDS_${PN}-plugins-base += "murphy"

#RDEPENDS of murphy-glib (${PN}-glib)
RDEPENDS_${PN}-glib += "murphy-core"

#RDEPENDS of murphy-glib-dev (${PN}-glib-dev)
RDEPENDS_${PN}-glib-dev += "murphy-core"
RDEPENDS_${PN}-glib-dev += "murphy-glib"

#RDEPENDS of murphy-ecore-dev (${PN}-ecore-dev)
RDEPENDS_${PN}-ecore-dev += "murphy-core"
RDEPENDS_${PN}-ecore-dev += "murphy-ecore"


DEPENDS = ""
#DEPENDS of murphy
DEPENDS += "genivi-shell"
DEPENDS += "ofono"
DEPENDS += "json-c"
DEPENDS += "libxml2"
DEPENDS += "audio-session-manager"
DEPENDS += "aul"
DEPENDS += "systemd"
inherit pkgconfig
DEPENDS += "glib-2.0"
DEPENDS += "lua"
DEPENDS += "libcap"
DEPENDS += "ico-uxf-weston-plugin"
DEPENDS += "flex"
DEPENDS += "tizen-platform-config"
DEPENDS += "weston-ivi-shell"
DEPENDS += "smack"
DEPENDS += "libwebsockets"
DEPENDS += "ecore"
DEPENDS += "virtual/libgles2"
DEPENDS += "virtual/egl"
DEPENDS += "dbus"
DEPENDS += "pulseaudio"
DEPENDS += "ail"
DEPENDS_append_class-native = " bison-native"
DEPENDS_append_class-target = " bison-native"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/murphy.manifest .
 echo "Build with icosyscon"
 
 
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
  
  
  CONFIG_OPTIONS=""
  DYNAMIC_PLUGINS="domain-control,system-controller,ivi-resource-manager"
  
  CONFIG_OPTIONS="$CONFIG_OPTIONS --enable-gpl --enable-pulse"
  
  CONFIG_OPTIONS="$CONFIG_OPTIONS --enable-gpl --enable-ecore"
  
  CONFIG_OPTIONS="$CONFIG_OPTIONS --enable-gpl --enable-glib"
  
  CONFIG_OPTIONS="$CONFIG_OPTIONS --disable-qt"
  
  CONFIG_OPTIONS="$CONFIG_OPTIONS --enable-gpl --enable-libdbus"
  
  CONFIG_OPTIONS="$CONFIG_OPTIONS --enable-gpl --enable-telephony"
  
  CONFIG_OPTIONS="$CONFIG_OPTIONS --enable-resource-asm"
  DYNAMIC_PLUGINS="$DYNAMIC_PLUGINS,resource-asm"
  
  CONFIG_OPTIONS="$CONFIG_OPTIONS --enable-websockets"
  
  CONFIG_OPTIONS="$CONFIG_OPTIONS --enable-smack"
  
  CONFIG_OPTIONS="$CONFIG_OPTIONS --enable-system-controller"
  
  CONFIG_OPTIONS="$CONFIG_OPTIONS --enable-system-monitor"
  
  ./bootstrap
  
  autotools_do_configure
  oe_runmake clean
  oe_runmake ${PARALLEL_MAKE} $V
  
  
  
}
EXTRA_OECONF += " $CONFIG_OPTIONS --with-dynamic-plugins=$DYNAMIC_PLUGINS"

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
 
 # Make sure we have a plugin dir even if all the basic plugins
 # are configured to be built in.
 mkdir -p ${D}${prefix}/lib/murphy/plugins
 
 # Get rid of any *.la files installed by libtool.
 rm -f ${D}${prefix}/lib/*.la
 
 # Clean up also the murphy DB installation.
 rm -f ${D}${prefix}/lib/murphy/*.la
 
 # Generate list of linkedin plugins (depends on the configuration).
 outdir="`pwd`"
 cd ${D} 
 find ./${prefix}/lib -name libmurphy-plugin-*.so* | \
 sed 's#^./*#/#g' > $outdir/filelist.plugins-base 
 cd $(outdir)
 echo "Found the following linked-in plugin files:"
 cat $outdir/filelist.plugins-base | sed 's/^/    /g'
 
 # Generate list of header files, filtering ones that go to subpackages.
 outdir="`pwd`"
 cd ${D}
 find ./${prefix}/include/murphy | \
 grep -E -v '((pulse)|(ecore)|(glib)|(qt))-glue' | \
 sed 's#^./*#/#g' > $outdir/filelist.devel-includes 
 cd $(outdir)
 
 # Replace the default sample/test config files with the packaging ones.
 rm -f ${D}${sysconfdir}/murphy/*
 cp packaging.in/murphy-lua.conf ${D}${sysconfdir}/murphy/murphy.conf
 cp packaging.in/murphy.lua      ${D}${sysconfdir}/murphy/murphy.lua
 
 # Copy plugin configuration files in place.
 mkdir -p ${D}${sysconfdir}/murphy/plugins/amb
 cp packaging.in/amb-config.lua \
 ${D}${sysconfdir}/murphy/plugins/amb/config.lua
 
 # Copy tmpfiles.d config file in place
 mkdir -p ${D}/usr/lib/tmpfiles.d
 cp packaging.in/murphyd.conf ${D}/usr/lib/tmpfiles.d
 
 # Copy the systemd files in place.
 #mkdir -p %{buildroot}%{_unitdir}
 mkdir -p ${D}${prefix}/lib/systemd/user
 cp packaging.in/murphyd.service ${D}${prefix}/lib/systemd/user
 
 mkdir -p ${D}${sysconfdir}/dbus-1/system.d
 sed "s/@TZ_SYS_USER_GROUP@/users/g" \
     packaging.in/org.Murphy.conf.in > packaging.in/org.Murphy.conf
 cp packaging.in/org.Murphy.conf \
     ${D}${sysconfdir}/dbus-1/system.d/org.Murphy.conf
 
 # copy (experimental) GAM resource backend configuration files
 mkdir -p ${D}${sysconfdir}/murphy/gam
 cp packaging.in/gam-*.names packaging.in/gam-*.tree \
     ${D}${sysconfdir}/murphy/gam
 
 
}

pkg_postinst_${PN}() {
    #!/bin/sh -e

    ldconfig

}

pkg_postinst_${PN}() {
    #!/bin/sh -e

    /bin/systemctl --user enable --global murphyd.service
    setcap 'cap_net_admin=+ep' $D${prefix}/bin/murphyd
    ldconfig

}

pkg_postinst_${PN}() {
    #!/bin/sh -e

    ldconfig

}

pkg_postinst_${PN}() {
    #!/bin/sh -e

    ldconfig

}

pkg_postinst_${PN}() {
    #!/bin/sh -e

    ldconfig

}

pkg_postinst_${PN}() {
    #!/bin/sh -e

    ldconfig

}

pkg_postinst_${PN}() {
    #!/bin/sh -e

    ldconfig

}

pkg_postrm_${PN}() {
    #!/bin/sh -e

    ldconfig

}

pkg_postrm_${PN}() {
    #!/bin/sh -e

    if [ "$1" = "0" ]; then
    systemctl --user disable --global murphyd.service
    fi
    ldconfig

}

pkg_postrm_${PN}() {
    #!/bin/sh -e

    ldconfig

}

pkg_postrm_${PN}() {
    #!/bin/sh -e

    ldconfig

}

pkg_postrm_${PN}() {
    #!/bin/sh -e

    ldconfig

}

pkg_postrm_${PN}() {
    #!/bin/sh -e

    ldconfig

}

pkg_postrm_${PN}() {
    #!/bin/sh -e

    ldconfig

}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " murphy-core "
PACKAGES += " murphy-dev "
PACKAGES += " murphy-ecore "
PACKAGES += " murphy-gam-dev "
PACKAGES += " murphy-pulse "
PACKAGES += " murphy "
PACKAGES += " murphy-ivi-resource-manager "
PACKAGES += " murphy-ecore-dev "
PACKAGES += " murphy-pulse-dev "
PACKAGES += " murphy-tests "
PACKAGES += " murphy-gam "
PACKAGES += " murphy-system-controller "
PACKAGES += " murphy-glib "
PACKAGES += " murphy-glib-dev "
PACKAGES += " murphy-plugins-base "

murphy-core_files = ""
murphy-core_files += "${prefix}/lib/libmurphy-common.so.*"
murphy-core_files += "${prefix}/lib/libmurphy-core.so.*"
murphy-core_files += "${prefix}/lib/libmurphy-resolver.so.*"
murphy-core_files += "${prefix}/lib/libmurphy-resource.so.*"
murphy-core_files += "${prefix}/lib/libmurphy-resource-backend.so.*"
murphy-core_files += "${prefix}/lib/libmurphy-lua-utils.so.*"
murphy-core_files += "${prefix}/lib/libmurphy-lua-decision.so.*"
murphy-core_files += "${prefix}/lib/libmurphy-domain-controller.so.*"
murphy-core_files += "${prefix}/lib/murphy/*.so.*"
murphy-core_files += "${prefix}/lib/libbreedline*.so.*"
murphy-core_files += "${prefix}/lib/libmurphy-libdbus.so.*"
murphy-core_files += "${prefix}/lib/libmurphy-dbus-libdbus.so.*"

murphy-dev_files = ""
murphy-dev_files += "${prefix}/include/murphy-db"
murphy-dev_files += "${prefix}/lib/libmurphy-common.so"
murphy-dev_files += "${prefix}/lib/libmurphy-core.so"
murphy-dev_files += "${prefix}/lib/libmurphy-resolver.so"
murphy-dev_files += "${prefix}/lib/libmurphy-resource.so"
murphy-dev_files += "${prefix}/lib/libmurphy-resource-backend.so"
murphy-dev_files += "${prefix}/lib/libmurphy-lua-utils.so"
murphy-dev_files += "${prefix}/lib/libmurphy-lua-decision.so"
murphy-dev_files += "${prefix}/lib/libmurphy-domain-controller.so"
murphy-dev_files += "${prefix}/lib/murphy/*.so"
murphy-dev_files += "${prefix}/lib/pkgconfig/murphy-common.pc"
murphy-dev_files += "${prefix}/lib/pkgconfig/murphy-core.pc"
murphy-dev_files += "${prefix}/lib/pkgconfig/murphy-resolver.pc"
murphy-dev_files += "${prefix}/lib/pkgconfig/murphy-lua-utils.pc"
murphy-dev_files += "${prefix}/lib/pkgconfig/murphy-lua-decision.pc"
murphy-dev_files += "${prefix}/lib/pkgconfig/murphy-domain-controller.pc"
murphy-dev_files += "${prefix}/lib/pkgconfig/murphy-db.pc"
murphy-dev_files += "${prefix}/lib/pkgconfig/murphy-resource.pc"
murphy-dev_files += "${prefix}/include/breedline"
murphy-dev_files += "${prefix}/lib/libbreedline*.so"
murphy-dev_files += "${prefix}/lib/pkgconfig/breedline*.pc"
murphy-dev_files += "${prefix}/lib/libmurphy-libdbus.so"
murphy-dev_files += "${prefix}/lib/libmurphy-dbus-libdbus.so"
murphy-dev_files += "${prefix}/lib/pkgconfig/murphy-libdbus.pc"
murphy-dev_files += "${prefix}/lib/pkgconfig/murphy-dbus-libdbus.pc"

murphy-ecore_files = ""
murphy-ecore_files += "${prefix}/lib/libmurphy-ecore.so.*"
MANIFESTFILES_${PN}-ecore = "murphy.manifest"

murphy-gam-dev_files = ""
murphy-gam-dev_files += "${prefix}/bin/decision-test"
murphy-gam-dev_files += "${prefix}/bin/pattern-generator"
murphy-gam-dev_files += "${prefix}/lib/libmurphy-decision-tree.so"

murphy-pulse_files = ""
murphy-pulse_files += "${prefix}/lib/libmurphy-pulse.so.*"
MANIFESTFILES_${PN}-pulse = "murphy.manifest"

murphy-doc_files = ""
murphy-doc_files += "${prefix}/share/doc/murphy/AUTHORS"
murphy-doc_files += "${prefix}/share/doc/murphy/CODING-STYLE"
murphy-doc_files += "${prefix}/share/doc/murphy/ChangeLog"
murphy-doc_files += "${prefix}/share/doc/murphy/NEWS"
murphy-doc_files += "${prefix}/share/doc/murphy/README"

murphy_files = ""
murphy_files += "${prefix}/bin/murphyd"
murphy_files += "${sysconfdir}/murphy"
murphy_files += "${prefix}/lib/systemd/user/murphyd.service"
murphy_files += "/usr/lib/tmpfiles.d/murphyd.conf"
murphy_files += "${prefix}/sbin/asm-bridge"
murphy_files += "${sysconfdir}/dbus-1/system.d"
murphy_files += "${sysconfdir}/dbus-1/system.d/org.Murphy.conf"
murphy_files += "${prefix}/share/murphy"
CONFFILES_${PN} = ""
CONFFILES_${PN} += "${sysconfdir}/murphy"
CONFFILES_${PN} += "${sysconfdir}/dbus-1/system.d/org.Murphy.conf"
MANIFESTFILES_${PN} = "murphy.manifest"

murphy-ivi-resource-manager_files = ""
murphy-ivi-resource-manager_files += "${prefix}/lib/murphy/plugins/plugin-ivi-resource-manager.so"
MANIFESTFILES_${PN}-ivi-resource-manager = "murphy.manifest"

murphy-ecore-dev_files = ""
murphy-ecore-dev_files += "${prefix}/include/murphy/common/ecore-glue.h"
murphy-ecore-dev_files += "${prefix}/lib/libmurphy-ecore.so"
murphy-ecore-dev_files += "${prefix}/lib/pkgconfig/murphy-ecore.pc"

murphy-pulse-dev_files = ""
murphy-pulse-dev_files += "${prefix}/include/murphy/common/pulse-glue.h"
murphy-pulse-dev_files += "${prefix}/lib/libmurphy-pulse.so"
murphy-pulse-dev_files += "${prefix}/lib/pkgconfig/murphy-pulse.pc"

murphy-tests_files = ""
murphy-tests_files += "${prefix}/bin/resource-client"
murphy-tests_files += "${prefix}/bin/resource-api-test"
murphy-tests_files += "${prefix}/bin/resource-api-fuzz"
murphy-tests_files += "${prefix}/bin/resource-context-create"
murphy-tests_files += "${prefix}/bin/test-domain-controller"
murphy-tests_files += "${prefix}/bin/murphy-console"
MANIFESTFILES_${PN}-tests = "murphy.manifest"

murphy-gam_files = ""
murphy-gam_files += "${prefix}/lib/libmurphy-decision-tree.so.*"
murphy-gam_files += "${prefix}/lib/libmurphy-decision-tree.so.0.0.0"
murphy-gam_files += "${prefix}/lib/murphy/plugins/plugin-gam-resource-manager.so"

murphy-system-controller_files = ""
murphy-system-controller_files += "${prefix}/lib/murphy/plugins/plugin-system-controller.so"
MANIFESTFILES_${PN}-system-controller = "murphy.manifest"

murphy-glib_files = ""
murphy-glib_files += "${prefix}/lib/libmurphy-glib.so.*"
MANIFESTFILES_${PN}-glib = "murphy.manifest"

murphy-glib-dev_files = ""
murphy-glib-dev_files += "${prefix}/include/murphy/common/glib-glue.h"
murphy-glib-dev_files += "${prefix}/lib/libmurphy-glib.so"
murphy-glib-dev_files += "${prefix}/lib/pkgconfig/murphy-glib.pc"

murphy-plugins-base_files = ""
murphy-plugins-base_files += "${prefix}/lib/murphy/plugins/plugin-domain-control.so"
murphy-plugins-base_files += "${prefix}/lib/murphy/plugins/plugin-resource-asm.so"
murphy-plugins-base_files += "${prefix}/lib/murphy/plugins/plugin-resource-native.so"

FILES_${PN}-core = "${murphy-core_files}"
FILES_${PN}-dev = "${murphy-dev_files}"
FILES_${PN}-ecore = "${murphy-ecore_files}"
FILES_${PN}-gam-dev = "${murphy-gam-dev_files}"
FILES_${PN}-pulse = "${murphy-pulse_files}"
FILES_${PN}-doc = "${murphy-doc_files}"
FILES_${PN} = "${murphy_files}"
FILES_${PN}-ivi-resource-manager = "${murphy-ivi-resource-manager_files}"
FILES_${PN}-ecore-dev = "${murphy-ecore-dev_files}"
FILES_${PN}-pulse-dev = "${murphy-pulse-dev_files}"
FILES_${PN}-tests = "${murphy-tests_files}"
FILES_${PN}-gam = "${murphy-gam_files}"
FILES_${PN}-system-controller = "${murphy-system-controller_files}"
FILES_${PN}-glib = "${murphy-glib_files}"
FILES_${PN}-glib-dev = "${murphy-glib-dev_files}"
FILES_${PN}-plugins-base = "${murphy-plugins-base_files}"

PKG_murphy-core= "murphy-core"
PKG_murphy-dev= "murphy-dev"
PKG_murphy-ecore= "murphy-ecore"
PKG_murphy-gam-dev= "murphy-gam-dev"
PKG_murphy-pulse= "murphy-pulse"
PKG_murphy-doc= "murphy-doc"
PKG_murphy= "murphy"
PKG_murphy-ivi-resource-manager= "murphy-ivi-resource-manager"
PKG_murphy-ecore-dev= "murphy-ecore-dev"
PKG_murphy-pulse-dev= "murphy-pulse-dev"
PKG_murphy-tests= "murphy-tests"
PKG_murphy-gam= "murphy-gam"
PKG_murphy-system-controller= "murphy-system-controller"
PKG_murphy-glib= "murphy-glib"
PKG_murphy-glib-dev= "murphy-glib-dev"
PKG_murphy-plugins-base= "murphy-plugins-base"

require murphy-extraconf.inc

