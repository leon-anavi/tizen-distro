DESCRIPTION = "GLib based Single Sign-On daemon"
HOMEPAGE = "http://nohomepage.org"
SECTION = "Security/Accounts"
LICENSE = "LGPL-2.1+ and GPL-2.0+"
PV = "1.0.3"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by gsignond-doc
PROVIDES += "gsignond-doc"


#PROVIDES by gsignond
# the PROVIDES rules is ignore "gsignon  "
PROVIDES += "gsignon"
RPROVIDES_gsignond += "gsignon"


#PROVIDES by gsignond-dev
PROVIDES += "gsignond-dev"


RDEPENDS = ""
#RDEPENDS of gsignond-doc (${PN}-doc)
RDEPENDS_${PN}-doc += "gsignond"

#RDEPENDS of gsignond (${PN})
RDEPENDS_${PN} += "glibc"

#RDEPENDS of gsignond-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "gsignond"


DEPENDS = ""
#DEPENDS of gsignond
inherit pkgconfig
DEPENDS += "glib-2.0"
DEPENDS += "ecryptfs-utils"
DEPENDS += "smack"
DEPENDS += "sqlite3"
DEPENDS += "dbus"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q -n gsignond-1.0.3
 cp ${S}/packaging/gsignond.manifest .
 cp ${S}/packaging/gsignond-cleandb .
 
 
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
  
  autoreconf -ivf
  
  autotools_do_configure
  
  oe_runmake ${PARALLEL_MAKE}
  
  
  
}
EXTRA_OECONF += " --enable-dbus-type=p2p"

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
 install -m 755 -d ${D}${prefix}/lib/systemd/user
 install -m 644 data/gsignond.service ${D}${prefix}/lib/systemd/user/
 install -m 755 -d ${D}${prefix}/lib/systemd/user/default.target.wants
 ln -sf ../gsignond.service ${D}${prefix}/lib/systemd/user/default.target.wants/gsignond.service
 install -m 755 -d ${D}${sysconfdir}/gumd/userdel.d/
 install -m 755 gsignond-cleandb ${D}${sysconfdir}/gumd/userdel.d/
 
 
}

pkg_postinst_${PN}() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
    chmod u+s $D${prefix}/bin/gsignond
    getent group gsignond > /dev/null || /usr/sbin/groupadd -r gsignond

}

pkg_postrm_${PN}() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " gsignond "
PACKAGES += " gsignond-dev "

gsignond-doc_files = ""
gsignond-doc_files += "${prefix}/share/gtk-doc/html/gsignond/*"

gsignond_files = ""
gsignond_files += "AUTHORS COPYING.LIB"
gsignond_files += "${prefix}/bin/gsignond"
gsignond_files += "${prefix}/lib/libgsignond-*.so.*"
gsignond_files += "${prefix}/lib/gsignond/extensions/*.so*"
gsignond_files += "${prefix}/lib/gsignond/gplugins/*.so*"
gsignond_files += "${prefix}/lib/gsignond/pluginloaders/gsignond-plugind"
gsignond_files += "${prefix}/lib/systemd/user/gsignond.service"
gsignond_files += "${prefix}/lib/systemd/user/default.target.wants/gsignond.service"
gsignond_files += "${sysconfdir}/gsignond.conf"
gsignond_files += "${sysconfdir}/gumd/userdel.d/"
MANIFESTFILES_${PN} = "gsignond.manifest"

gsignond-dev_files = ""
gsignond-dev_files += "${prefix}/include/gsignond/*.h"
gsignond-dev_files += "${prefix}/lib/libgsignond-*.so"
gsignond-dev_files += "${prefix}/lib/pkgconfig/gsignond.pc"

FILES_${PN}-doc = "${gsignond-doc_files}"
FILES_${PN} = "${gsignond_files}"
FILES_${PN}-dev = "${gsignond-dev_files}"

PKG_gsignond-doc= "gsignond-doc"
PKG_gsignond= "gsignond"
PKG_gsignond-dev= "gsignond-dev"

require gsignond-extraconf.inc

