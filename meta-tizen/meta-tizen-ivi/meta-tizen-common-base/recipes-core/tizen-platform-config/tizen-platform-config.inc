DESCRIPTION = "Tizen Platform Configuration"
HOMEPAGE = "http://www.tizen.org"
SECTION = "System/Configuration"
LICENSE = "MIT"
PV = "2.0"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by tizen-platform-config


#PROVIDES by libtzplatform-config-dev
PROVIDES += "libtzplatform-config-dev"


#PROVIDES by tizen-platform-config-tools
PROVIDES += "tizen-platform-config-tools"


#PROVIDES by libtzplatform-config
PROVIDES += "libtzplatform-config"


RDEPENDS = ""
#RDEPENDS of tizen-platform-config-tools (${PN}-tools)
RDEPENDS_${PN}-tools += "libtzplatform-config"

#RDEPENDS of tizen-platform-config (${PN})
RDEPENDS_${PN} += "smack"

#RDEPENDS of libtzplatform-config-dev (libtzplatform-config-dev)
RDEPENDS_libtzplatform-config-dev += "libtzplatform-config"

#RDEPENDS of libtzplatform-config (libtzplatform-config)
RDEPENDS_libtzplatform-config += "tizen-platform-config"


DEPENDS = ""
#DEPENDS of tizen-platform-config
DEPENDS += "tizen-platform-wrapper"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/tizen-platform-config.manifest .
 
 
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
  
  
  autotools_do_configure
  oe_runmake ${PARALLEL_MAKE}
  
  exit 0
  oe_runmake check
  
  
  
}
EXTRA_OECONF += " --enable-static"

do_install() {
 export RPM_BUILD_ROOT=${D}
 cd ${S}
 LANG=C
 export LANG
 unset DISPLAY
 rm -rf ${D}
 mkdir -p ${D}
 
 
   oe_runmake \
         DESTDIR=${D} \
         INSTALL_ROOT=${D} \
         BINDIR=${prefix}/bin \
   install  
   rm -f ${D}${infodir}/dir 
   find ${D} -regex ".*\.la$" | xargs rm -f -- 
   
 
 
}

pkg_postinst_libtzplatform-config() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postinst_${PN}() {
    #!/bin/sh -e

    ##############################################
    # BEGIN - creation of the /etc/skel/content
    ##############################################
    saveHOME="$HOME"
    HOME="$D${sysconfdir}/skel"
    . "$D${sysconfdir}/tizen-platform.conf"
    cat << ENDOFCAT |
    $TZ_USER_HOME        User::Home           true
    $TZ_USER_CONTENT     User::Home           true
    $TZ_USER_CAMERA      User::App::Shared    true
    $TZ_USER_DOCUMENTS   User::App::Shared    true
    $TZ_USER_DOWNLOADS   User::App::Shared    true
    $TZ_USER_GAMES       User::App::Shared    true
    $TZ_USER_IMAGES      User::App::Shared    true
    $TZ_USER_OTHERS      User::App::Shared    true
    $TZ_USER_SOUNDS      User::App::Shared    true
    $TZ_USER_VIDEOS      User::App::Shared    true
    $TZ_USER_SHARE       User::App::Shared    true
    $TZ_USER_APP         User                 false
    $TZ_USER_DB          User                 false
    $TZ_USER_DESKTOP     User                 false
    $TZ_USER_ICONS       User::Home           true
    $TZ_USER_PACKAGES    User                 false
    ENDOFCAT
    LANG= sort | while read skelname context transmute; do
    	mkdir -p "$skelname"
    	chsmack -a "$context" "$skelname"
    	[ "$transmute" = true ] && chsmack -t "$skelname"
    done
    HOME="$saveHOME"
    ##############################################
    # END - creation of the /etc/skel/content
    ##############################################

}

pkg_postrm_libtzplatform-config() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " libtzplatform-config-dev "
PACKAGES += " tizen-platform-config-tools "
PACKAGES += " tizen-platform-config "
PACKAGES += " libtzplatform-config "

libtzplatform-config-dev_files = ""
libtzplatform-config-dev_files += "${prefix}/lib/*.so"
libtzplatform-config-dev_files += "${prefix}/lib/pkgconfig/*.pc"
libtzplatform-config-dev_files += "${prefix}/include/*.h"
libtzplatform-config-dev_files += "${sysconfdir}/rpm/macros.tizen-platform"
libtzplatform-config-dev_files += "${prefix}/lib/*.a"
CONFFILES_libtzplatform-config-dev = ""
CONFFILES_libtzplatform-config-dev += "${sysconfdir}/rpm/macros.tizen-platform"
MANIFESTFILES_libtzplatform-config-dev = "tizen-platform-config.manifest"

tizen-platform-config-tools_files = ""
tizen-platform-config-tools_files += "${prefix}/bin/*"
MANIFESTFILES_${PN}-tools = "tizen-platform-config.manifest"

tizen-platform-config_files = ""
tizen-platform-config_files += "${sysconfdir}/tizen-platform.conf"
CONFFILES_${PN} = ""
CONFFILES_${PN} += "${sysconfdir}/tizen-platform.conf"
MANIFESTFILES_${PN} = "tizen-platform-config.manifest"

libtzplatform-config_files = ""
libtzplatform-config_files += "${prefix}/lib/*.so.*"
MANIFESTFILES_libtzplatform-config = "tizen-platform-config.manifest"

FILES_libtzplatform-config-dev = "${libtzplatform-config-dev_files}"
FILES_${PN}-tools = "${tizen-platform-config-tools_files}"
FILES_${PN} = "${tizen-platform-config_files}"
FILES_libtzplatform-config = "${libtzplatform-config_files}"

PKG_libtzplatform-config-dev= "libtzplatform-config-dev"
PKG_tizen-platform-config-tools= "tizen-platform-config-tools"
PKG_tizen-platform-config= "tizen-platform-config"
PKG_libtzplatform-config= "libtzplatform-config"

require tizen-platform-config-extraconf.inc

