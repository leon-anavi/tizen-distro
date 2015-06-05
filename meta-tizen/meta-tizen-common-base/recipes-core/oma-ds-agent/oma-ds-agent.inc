DESCRIPTION = "OMA-DS Agent Daemon for Data Synchronization"
HOMEPAGE = "http://nohomepage.org"
SECTION = "Base/Device Management"
LICENSE = "Apache-2.0"
PV = "0.1.66"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by oma-ds-agent


#PROVIDES by ds-public-plugins
PROVIDES += "ds-public-plugins"


RDEPENDS = ""
#RDEPENDS of oma-ds-agent (${PN})
RDEPENDS_${PN} += "glibc"


DEPENDS = ""
#DEPENDS of oma-ds-agent
DEPENDS += "libcheck"
inherit tizen_cmake
DEPENDS += "libslp-memo"
DEPENDS += "tizen-platform-config"
DEPENDS += "expat"
inherit pkgconfig
DEPENDS += "dlog"
DEPENDS += "glib-2.0"
DEPENDS += "libsoup-2.4"
DEPENDS += "contacts-service"
DEPENDS += "aul"
DEPENDS += "sync-agent"
DEPENDS += "sqlite3"
DEPENDS += "vconf"
DEPENDS += "dbus-glib"

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
         ${EXTRA_OECMAKE} . -DCMAKE_INSTALL_PREFIX=${prefix} -DTZ_SYS_DB=${prefix}/dbspace
 make ${PARALLEL_MAKE}
 
 
 
 
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
 
 if [ ! -d ${D}${prefix}/dbspace ]
 then
 	mkdir -p ${D}${prefix}/dbspace
 fi
 
 sqlite3 ${D}${prefix}/dbspace/.omasyncagent.db "PRAGMA journal_mode = PERSIST; create table a(a); drop table a;" > /dev/null
 
 
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

    if [ ! -d $D${prefix}/dbspace ]
    then
    	mkdir $D${prefix}/dbspace
    fi
    if [ ! -d $D${sysconfdir}/rc.d/rc3.d ]
    then
    	mkdir $D${sysconfdir}/rc.d/rc3.d
    fi
    if [ ! -d $D${sysconfdir}/rc.d/rc5.d ]
    then
    	mkdir $D${sysconfdir}/rc.d/rc5.d
    fi

}

pkg_postrm_${PN}() {
    #!/bin/sh -e

    rm -f /tmp/agent_fw_event_omads*
    rm -f /tmp/agent_fw_noti_reply_omads*
    rm -f $D${sysconfdir}/rc.d/rc3.d/S91oma-ds-agent
    rm -f $D${sysconfdir}/rc.d/rc5.d/S91oma-ds-agent
    rm -f $D${prefix}/dbspace/.omasyncagent.db $D${prefix}/dbspace/.omasyncagent.db-journal
    rm -rf /usr/share/oma-ds-cfg

}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " oma-ds-agent "
PACKAGES += " ds-public-plugins "

oma-ds-agent_files = ""
oma-ds-agent_files += "${prefix}/dbspace/.omasyncagent.db"
oma-ds-agent_files += "${prefix}/dbspace/.omasyncagent.db-journal"
oma-ds-agent_files += "/usr/share/dbus-1/system-services/com.samsung.omadsagent.service"
oma-ds-agent_files += "${prefix}/bin/oma-ds-agent"
oma-ds-agent_files += "/usr/share/oma-ds-cfg/*"
oma-ds-agent_files += "/usr/lib/systemd/system/oma-ds-agent.service"
oma-ds-agent_files += "/usr/lib/systemd/system/graphical.target.wants/oma-ds-agent.service"
oma-ds-agent_files += "${sysconfdir}/dbus-1/system.d/com.samsung.omadsagent.conf"
MANIFESTFILES_${PN} = "oma-ds-agent.manifest"

ds-public-plugins_files = ""
ds-public-plugins_files += "/usr/lib/sync-agent/ds-public/*"
MANIFESTFILES_ds-public-plugins = "ds-public-plugins.manifest"

FILES_${PN} = "${oma-ds-agent_files}"
FILES_ds-public-plugins = "${ds-public-plugins_files}"

PKG_oma-ds-agent= "oma-ds-agent"
PKG_ds-public-plugins= "ds-public-plugins"

require oma-ds-agent-extraconf.inc

