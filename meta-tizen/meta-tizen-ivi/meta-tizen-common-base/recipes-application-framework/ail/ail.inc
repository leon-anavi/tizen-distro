DESCRIPTION = "Application Information Library"
HOMEPAGE = "http://nohomepage.org"
SECTION = "Application Framework/Libraries"
LICENSE = "Apache-2.0"
PV = "0.2.80"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by ail
# the PROVIDES rules is ignore "libail = 0.2.80-0"
PROVIDES += "libail"
RPROVIDES_ail += "libail"


#PROVIDES by ail-dev
PROVIDES += "ail-dev"


#PROVIDES by ail-vconf-dev
PROVIDES += "ail-vconf-dev"


RDEPENDS = ""
#RDEPENDS of ail-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "tizen-platform-config"
RDEPENDS_${PN}-dev += "libail"
RDEPENDS_${PN}-dev += "smack"

#RDEPENDS of ail-vconf-dev (${PN}-vconf-dev)
RDEPENDS_${PN}-vconf-dev += "libail"


DEPENDS = ""
#DEPENDS of ail
inherit tizen_cmake
DEPENDS += "tizen-platform-config"
inherit pkgconfig
DEPENDS += "dlog"
DEPENDS += "smack"
DEPENDS += "sqlite3"
DEPENDS += "xdgmime"
DEPENDS += "vconf"
DEPENDS += "libslp-db-util"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/ail.manifest .
 
 
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
 
 CFLAGS="$CFLAGS -fpic"
 
 
 
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
         ${EXTRA_OECMAKE} .  -DTZ_SYS_RW_DESKTOP_APP=${prefix}/share/applications \
           -DBUILD_PKGTYPE=rpm
 
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

    ldconfig
    # Create tizenglobalapp user needed for global installation
    useradd -d $D${prefix}/apps -m tizenglobalapp -r -c "system user for common applications" -g root
    #mkdir -p %TZ_SYS_RW_APP/.config/xwalk-service/applications
    #cd %TZ_SYS_RW_APP/
    #ln -s .config/xwalk-service/applications/
    vconftool set -t string db/ail/ail_info "0" -f -s User
    vconftool set -t string db/menuscreen/desktop "0" -f -s User
    vconftool set -t string db/menu_widget/language "en_US.utf8" -f -s User
    mkdir -p $D${prefix}/share/applications
    mkdir -p $D${prefix}/share/applications
    mkdir -p $D${prefix}/apps
    mkdir -p $D${prefix}/dbspace
    mkdir -p $D${prefix}/share/icons/default/small
    chsmack -a '*' $D${prefix}/dbspace
    chsmack -a '*' $D${prefix}/apps
    chsmack -a '*' $D${prefix}/share/applications
    chsmack -a '*' $D${prefix}/share/applications
    chsmack -a '*' $D${prefix}/share/icons
    chsmack -a '*' $D${prefix}/share/icons/default
    chsmack -a '*' $D${prefix}/share/icons/default/small/
    chmod g+w $D${prefix}/share/applications
    chmod g+w $D${prefix}/share/applications
    chown tizenglobalapp:root $D${prefix}/share/applications
    chown tizenglobalapp:root $D${prefix}/share/applications
    chown tizenglobalapp:root $D${prefix}/apps
    chown tizenglobalapp:root $D${prefix}/dbspace
    chown tizenglobalapp:root $D${prefix}/dbspace
    chown tizenglobalapp:root -R $D${prefix}/share/icons
    ail_createdb 2>/dev/null
    ail_syncdb 2>/dev/null
    chsmack -a '*' $D${prefix}/dbspace/.app_info.db*
     

}

pkg_postrm_${PN}() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
    if [ $1 == 0 ]; then
        rm -f $D${prefix}/dbspace/.app_info.db*
    fi

}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " ail "
PACKAGES += " ail-dev "
PACKAGES += " ail-vconf-dev "

ail_files = ""
ail_files += "${prefix}/bin/ail_createdb"
ail_files += "${prefix}/bin/ail_createdb_user"
ail_files += "${prefix}/bin/ail_syncdb"
ail_files += "${prefix}/bin/ail_syncdb_user"
ail_files += "${prefix}/bin/ail_initdb"
ail_files += "${prefix}/bin/ail_initdb_user"
ail_files += "${prefix}/bin/ail_fota"
ail_files += "${prefix}/bin/ail_desktop"
ail_files += "${prefix}/bin/ail_filter"
ail_files += "${prefix}/bin/ail_list"
ail_files += "${prefix}/bin/ail_package"
ail_files += "${prefix}/share/install-info/*"
ail_files += "${prefix}/lib/libail.so.0"
ail_files += "${prefix}/lib/libail.so.0.1.0"
MANIFESTFILES_${PN} = "ail.manifest"

ail-dev_files = ""
ail-dev_files += "${prefix}/include/ail.h"
ail-dev_files += "${prefix}/lib/libail.so"
ail-dev_files += "${prefix}/lib/pkgconfig/ail.pc"
MANIFESTFILES_${PN}-dev = "ail.manifest"

ail-vconf-dev_files = ""
ail-vconf-dev_files += "${prefix}/include/ail_vconf.h"

FILES_${PN} = "${ail_files}"
FILES_${PN}-dev = "${ail-dev_files}"
FILES_${PN}-vconf-dev = "${ail-vconf-dev_files}"

PKG_ail= "ail"
PKG_ail-dev= "ail-dev"
PKG_ail-vconf-dev= "ail-vconf-dev"

require ail-extraconf.inc

