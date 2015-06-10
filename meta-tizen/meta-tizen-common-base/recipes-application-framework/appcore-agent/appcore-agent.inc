DESCRIPTION = "Agent Application basic"
HOMEPAGE = "http://nohomepage.org"
SECTION = "Application Framework/Service"
LICENSE = "Apache-2.0"
PV = "1.0"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by appcore-agent


#PROVIDES by appcore-agent-dev
PROVIDES += "appcore-agent-dev"


RDEPENDS = ""
#RDEPENDS of appcore-agent-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "appcore-agent"


DEPENDS = ""
#DEPENDS of appcore-agent
inherit tizen_cmake
inherit pkgconfig
DEPENDS += "dlog"
DEPENDS += "capi-appfw-application"
DEPENDS += "system-server"
DEPENDS += "aul"
DEPENDS += "glib-2.0"
DEPENDS += "vconf"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/appcore-agent.manifest .
 
 
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
         ${EXTRA_OECMAKE} .
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
 
 
   oe_runmake \
         DESTDIR=${D} \
         INSTALL_ROOT=${D} \
         BINDIR=${prefix}/bin \
   install  
   rm -f ${D}${infodir}/dir 
   find ${D} -regex ".*\.la$" | xargs rm -f -- 
   find ${D} -regex ".*\.a$" | xargs rm -f --
 
 
}

pkg_postinst_${PN}() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_${PN}() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " appcore-agent "
PACKAGES += " appcore-agent-dev "

appcore-agent_files = ""
appcore-agent_files += "${prefix}/lib/libappcore-agent.so.1"
appcore-agent_files += "${prefix}/lib/libappcore-agent.so.1.1"
MANIFESTFILES_${PN} = "appcore-agent.manifest"

appcore-agent-dev_files = ""
appcore-agent-dev_files += "${prefix}/lib/pkgconfig/appcore-agent.pc"
appcore-agent-dev_files += "${prefix}/lib/libappcore-agent.so"
appcore-agent-dev_files += "${prefix}/include/appcore-agent/appcore-agent.h"
appcore-agent-dev_files += "${prefix}/include/appcore-agent/service_app.h"
MANIFESTFILES_${PN}-dev = "appcore-agent.manifest"

FILES_${PN} = "${appcore-agent_files}"
FILES_${PN}-dev = "${appcore-agent-dev_files}"

PKG_appcore-agent= "appcore-agent"
PKG_appcore-agent-dev= "appcore-agent-dev"

require appcore-agent-extraconf.inc

