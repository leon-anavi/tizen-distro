DESCRIPTION = "Small Embeddable Language with Simple Procedural Syntax"
HOMEPAGE = "http://www.lua.org"
SECTION = "Base/Libraries"
LICENSE = "MIT"
PV = "5.1.4"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by lua


#PROVIDES by lua-dev
PROVIDES += "lua-dev"


#PROVIDES by liblua
PROVIDES += "liblua"


#PROVIDES by lua-doc
PROVIDES += "lua-doc"


RDEPENDS = ""
#RDEPENDS of lua-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "lua"


DEPENDS = ""
#DEPENDS of lua
DEPENDS_append_class-native = " readline-native"
DEPENDS_append_class-target = " readline-native"
inherit pkgconfig

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q -n lua-5.1.4
 cp ${S}/packaging/lua.manifest .
 
 
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
 
 export LDFLAGS+=" -Wl,-E -ldl -lreadline -lhistory -lncurses"
 sed -i 's:LUA_ROOT2 "LIBDIR/lua/5.1/":LUA_ROOT2 \"lib/lua/5.1/":' src/luaconf.h
 make ${PARALLEL_MAKE} -C src CC="${CC}" MYCFLAGS="$CFLAGS -fPIC -DLUA_USE_LINUX" MYLIBS="$LDFLAGS" V=5.1 all
 
 
 
}

do_install() {
 export RPM_BUILD_ROOT=${D}
 cd ${S}
 LANG=C
 export LANG
 unset DISPLAY
 rm -rf ${D}
 mkdir -p ${D}
 
 make install INSTALL_TOP="${D}${prefix}" INSTALL_LIB="${D}${prefix}/lib" INSTALL_CMOD=${D}${prefix}/lib/lua/5.1 INSTALL_MAN="${D}${mandir}/man1"
 install -D -m644 etc/lua.pc ${D}${prefix}/lib/pkgconfig/lua.pc
 for file in lua luac ; do
     mv "${D}${prefix}/bin/${file}"        "${D}${prefix}/bin/${file}5.1"
     mv "${D}${mandir}/man1/${file}.1" "${D}${mandir}/man1/${file}5.1.1"
 done
 install -d -m 0755 ${D}${prefix}/lib/lua/5.1
 install -d -m 0755 ${D}${prefix}/share/lua/5.1
 install -D -m644 ${S}/packaging/macros.lua ${D}${sysconfdir}/rpm/macros.lua
 
 chmod +x ${D}${prefix}/lib/liblua.so.5.1
 
 ln -s lua5.1 ${D}${prefix}/bin/lua
 
 
}

pkg_postinst_liblua() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_liblua() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " lua "
PACKAGES += " lua-dev "
PACKAGES += " liblua "

lua_files = ""
lua_files += "${mandir}/man1/lua5.1.1*"
lua_files += "${mandir}/man1/luac5.1.1*"
lua_files += "${prefix}/bin/lua"
lua_files += "${prefix}/bin/lua5.1"
lua_files += "${prefix}/bin/luac5.1"
lua_files += "${prefix}/lib/lua"
lua_files += "${prefix}/lib/lua/5.1"
lua_files += "${prefix}/share/lua"
lua_files += "${prefix}/share/lua/5.1"
lua_files += "${sysconfdir}/rpm/macros.lua"
MANIFESTFILES_${PN} = "lua.manifest"
DIRFILES_${PN} = ""
DIRFILES_${PN} += "${prefix}/lib/lua"
DIRFILES_${PN} += "${prefix}/lib/lua/5.1"
DIRFILES_${PN} += "${prefix}/share/lua"
DIRFILES_${PN} += "${prefix}/share/lua/5.1"

lua-dev_files = ""
lua-dev_files += "${prefix}/include/lauxlib.h"
lua-dev_files += "${prefix}/include/lua.h"
lua-dev_files += "${prefix}/include/lua.hpp"
lua-dev_files += "${prefix}/include/luaconf.h"
lua-dev_files += "${prefix}/include/lualib.h"
lua-dev_files += "${prefix}/lib/pkgconfig/lua.pc"
lua-dev_files += "${prefix}/lib/liblua.a"
lua-dev_files += "${prefix}/lib/liblua.so"
MANIFESTFILES_${PN}-dev = "lua.manifest"

liblua_files = ""
liblua_files += "${prefix}/lib/liblua.so.5.1"
MANIFESTFILES_lib${PN} = "lua.manifest"

lua-doc_files = ""
lua-doc_files += "doc/*"
MANIFESTFILES_${PN}-doc = "lua.manifest"

FILES_${PN} = "${lua_files}"
FILES_${PN}-dev = "${lua-dev_files}"
FILES_lib${PN} = "${liblua_files}"
FILES_${PN}-doc = "${lua-doc_files}"

PKG_lua= "lua"
PKG_lua-dev= "lua-dev"
PKG_liblua= "liblua"
PKG_lua-doc= "lua-doc"

require lua-extraconf.inc

