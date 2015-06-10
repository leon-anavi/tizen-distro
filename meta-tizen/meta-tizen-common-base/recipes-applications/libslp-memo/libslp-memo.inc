DESCRIPTION = "Memo DB interface library"
HOMEPAGE = "http://nohomepage.org"
SECTION = "Application Framework/Libraries"
LICENSE = "Flora"
PV = "0.1.5"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by libslp-memo


#PROVIDES by libslp-memo-dev
PROVIDES += "libslp-memo-dev"


RDEPENDS = ""
#RDEPENDS of libslp-memo-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "libslp-memo"


DEPENDS = ""
#DEPENDS of libslp-memo
inherit tizen_cmake
DEPENDS += "tizen-platform-config"
inherit pkgconfig
DEPENDS += "dlog"
DEPENDS += "sqlite3"
DEPENDS += "heynoti"
DEPENDS += "vconf"
DEPENDS += "libslp-db-util"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/libslp-memo.manifest .
 
 
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

    mkdir -p $D${prefix}/dbspace
    sqlite3 $D${prefix}/dbspace/.memo.db 'PRAGMA journal_mode = PERSIST;
    CREATE TABLE if not exists memo ( id INTEGER PRIMARY KEY autoincrement, content TEXT, written_time TEXT, create_time INTEGER, modi_time INTEGER, delete_time INTEGER, doodle INTEGER, color INTEGER, comment TEXT, favorite INTEGER,font_respect INTEGER, font_size INTEGER, font_color INTEGER, doodle_path TEXT );
                                  '
    [ "x$D" == "x" ] && ldconfig
    # Change file owner
    chown :users $D${prefix}/dbspace/.memo.db
    chown :users $D${prefix}/dbspace/.memo.db-journal
    # Change file permissions
    chmod 660  $D${prefix}/dbspace/.memo.db
    chmod 660  $D${prefix}/dbspace/.memo.db-journal
    chsmack -a 'User' $D${prefix}/dbspace/.memo.db*

}

pkg_postrm_${PN}() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " libslp-memo "
PACKAGES += " libslp-memo-dev "

libslp-memo_files = ""
libslp-memo_files += "${prefix}/lib/*.so.*"
MANIFESTFILES_${PN} = "libslp-memo.manifest"

libslp-memo-dev_files = ""
libslp-memo-dev_files += "${prefix}/lib/*.so"
libslp-memo-dev_files += "${prefix}/lib/pkgconfig/memo.pc"
libslp-memo-dev_files += "${prefix}/include/*.h"
MANIFESTFILES_${PN}-dev = "libslp-memo.manifest"

FILES_${PN} = "${libslp-memo_files}"
FILES_${PN}-dev = "${libslp-memo-dev_files}"

PKG_libslp-memo= "libslp-memo"
PKG_libslp-memo-dev= "libslp-memo-dev"

require libslp-memo-extraconf.inc

