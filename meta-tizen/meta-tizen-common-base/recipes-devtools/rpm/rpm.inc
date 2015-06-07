DESCRIPTION = "The Package Manager"
HOMEPAGE = "http://www.rpm.org"
SECTION = "Base/Package Management"
LICENSE = "GPL-2.0+"
PV = "4.11.0.1"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by rpm-security-plugin
PROVIDES += "rpm-security-plugin"


#PROVIDES by python-rpm
PROVIDES += "python-rpm"


#PROVIDES by rpm-build
PROVIDES += "rpm-build"
# the PROVIDES rules is ignore "rpmbuild  "
PROVIDES += "rpmbuild"
RPROVIDES_rpm-build += "rpmbuild"
# the PROVIDES rules is ignore "rpm:${prefix}/bin/rpmbuild  "
PROVIDES += "rpm:${prefix}/bin/rpmbuild"
RPROVIDES_rpm-build += "rpm:${prefix}/bin/rpmbuild"


#PROVIDES by rpm-dev
PROVIDES += "rpm-dev"


#PROVIDES by rpm
# the PROVIDES rules is ignore "rpminst  "
PROVIDES += "rpminst"
RPROVIDES_rpm += "rpminst"
# the PROVIDES rules is ignore "rpm-libs  "
PROVIDES += "rpm-libs"
RPROVIDES_rpm += "rpm-libs"


#PROVIDES by rpm-docs
PROVIDES += "rpm-docs "


RDEPENDS = ""
#RDEPENDS of rpm-security-plugin (${PN}-security-plugin)
RDEPENDS_${PN}-security-plugin += "smack"
RDEPENDS_${PN}-security-plugin += "nss"
RDEPENDS_${PN}-security-plugin += "rpm"

#RDEPENDS of python-rpm (python-${PN})
RDEPENDS_python-${PN} += "rpm"

#RDEPENDS of rpm-build (${PN}-build)
RDEPENDS_${PN}-build += "bzip2"
RDEPENDS_${PN}-build += "make"
RDEPENDS_${PN}-build += "gcc"
RDEPENDS_${PN}-build += "patch"
RDEPENDS_${PN}-build += "xz"
RDEPENDS_${PN}-build += "findutils"
RDEPENDS_${PN}-build += "gzip"
RDEPENDS_${PN}-build += "rpm"
RDEPENDS_${PN}-build += "glibc"
RDEPENDS_${PN}-build += "binutils"

#RDEPENDS of rpm-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "rpm"
RDEPENDS_${PN}-dev += "popt"


DEPENDS = ""
#DEPENDS of python-rpm
#DEPENDS of rpm
DEPENDS += "libxml2"
DEPENDS += "xz"
DEPENDS += "findutils"
DEPENDS += "file"
DEPENDS += "popt"
DEPENDS += "uthash"
DEPENDS += "nss"
DEPENDS += "make"
DEPENDS += "bzip2"
DEPENDS += "lua"
DEPENDS += "patch"
inherit pkgconfig
inherit pythonnative
DEPENDS += "libcap"
DEPENDS += "ncurses"
DEPENDS += "smack"
DEPENDS_append_class-native = " libtool"
DEPENDS_append_class-target = " libtool-cross"
#Replace "DEPENDS" on gettext by "inherit gettext"
inherit gettext
DEPENDS += "attr"
DEPENDS += "zlib"
DEPENDS += "acl"
DEPENDS += "gzip"
DEPENDS_append_class-native = " fdupes-native"
DEPENDS_append_class-target = " fdupes-native"
DEPENDS += "elfutils"
DEPENDS += "binutils"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q -n rpm-4.11.0.1
 cp ${S}/packaging/rpm.manifest .
 rm -rf sqlite
 tar xjf ${S}/packaging/db-4.8.30.tar.bz2
 ln -sfn db-4.8.30 db
 chmod -R u+w db/*
 # will get linked from db3
 rm -f rpmdb/db.h
 patch -p0 < ${S}/packaging/db-4.8.30-integration.dif
 if [ -s ${sysconfdir}/rpm/tizen_macros ]; then
     cp -a ${sysconfdir}/rpm/tizen_macros ${S}/packaging/rpm-tizen_macros
 fi
 cp -a ${S}/packaging/rpm-tizen_macros tizen_macros
 rm -f m4/libtool.m4
 rm -f m4/lt*.m4
 
 
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
  
  CPPFLAGS="$CPPFLAGS `pkg-config --cflags nss`"
  export CPPFLAGS
  export CFLAGS="$CFLAGS -ffunction-sections"
  export LDFLAGS="${LDFLAGS} -Wl,-Bsymbolic-functions -ffunction-sections"
  
  
  autotools_do_configure
  
  make ${PARALLEL_MAKE}
  
  
  
}
EXTRA_OECONF += " --disable-dependency-tracking --with-lua --with-acl --with-cap --enable-shared --enable-python --with-vendor=tizen --with-msm "

do_install() {
 export RPM_BUILD_ROOT=${D}
 cd ${S}
 LANG=C
 export LANG
 unset DISPLAY
 rm -rf ${D}
 mkdir -p ${D}
 
 mkdir -p ${D}${prefix}/lib
 mkdir -p ${D}${prefix}/share/locale
 ln -s ../share/locale ${D}${prefix}/lib/locale
 
   oe_runmake \
         DESTDIR=${D} \
         INSTALL_ROOT=${D} \
         BINDIR=${prefix}/bin \
   install  
   rm -f ${D}${infodir}/dir 
   find ${D} -regex ".*\.la$" | xargs rm -f -- 
   find ${D} -regex ".*\.a$" | xargs rm -f --
 install -m 644 db3/db.h ${D}${prefix}/include/rpm
 mkdir -p ${D}${sysconfdir}/rpm
 cp -a tizen_macros ${D}${prefix}/lib/rpm
 mkdir -p ${D}${prefix}/lib/rpm/tizen
 install -m 755 ${S}/packaging/find-docs.sh ${D}${prefix}/lib/rpm/tizen
 install -m 755 ${S}/packaging/find-provides.ksyms ${D}${prefix}/lib/rpm
 install -m 644 ${S}/packaging/device-sec-policy ${D}${sysconfdir}/device-sec-policy
 install -m 644 ${S}/packaging/device-sec-policy ${D}${prefix}/lib/rpm-plugins/msm-device-sec-policy
 ln -s ../tizen_macros ${D}${prefix}/lib/rpm/tizen/macros
 for d in BUILD RPMS SOURCES SPECS SRPMS BUILDROOT ; do
   mkdir -p ${D}${prefix}/src/packages/$d
   chmod 755 ${D}${prefix}/src/packages/$d
 done
 for d in ${D}${prefix}/lib/rpm/platform/*-linux/macros ; do
   dd=${d%-linux/macros}
   dd=${dd##*/}
   mkdir -p ${D}${prefix}/src/packages/RPMS/$dd
   chmod 755 ${D}${prefix}/src/packages/RPMS/$dd
 done
 mkdir -p ${D}${localstatedir}/lib/rpm
 gzip -9 ${D}${mandir}/man[18]/*.[18]
 export RPM_BUILD_ROOT
 chmod 755 doc/manual
 rm -rf doc/manual/Makefile*
 rm -f ${D}${prefix}/lib/rpmpopt
 rm -rf ${D}${mandir}/{fr,ja,ko,pl,ru,sk}
 rm -f ${D}${prefix}/share/locale/de/LC_MESSAGES/rpm.mo
 rm -f ${D}${prefix}/lib/rpm/cpanflute ${D}${prefix}/lib/rpm/cpanflute2
 install -m 755 scripts/find-supplements ${D}${prefix}/lib/rpm
 install -m 755 scripts/find-supplements.ksyms ${D}${prefix}/lib/rpm
 install -m 755 scripts/firmware.prov ${D}${prefix}/lib/rpm
 install -m 755 scripts/debuginfo.prov ${D}${prefix}/lib/rpm
 rm -f ${D}${prefix}/lib/locale ${D}${prefix}/lib/rpmrc
 mkdir -p ${D}${sysconfdir}/rpm
 chmod 755 ${D}${sysconfdir}/rpm
 mkdir -p ${D}${prefix}/lib/rpm/macros.d
 # remove some nonsense or non-working scripts
 for f in rpm2cpio.sh rpm.daily rpmdiff* rpm.log rpm.xinetd freshen.sh u_pkg.sh \
          magic magic.mgc magic.mime* rpmfile *.pl javadeps brp-redhat \
          brp-strip-static-archive vpkg-provides*.sh http.req sql.req tcl.req \
          rpmdb_* brp-sparc64-linux brp-strip-comment-note brp-java-gcjcompile
 do
     rm -f ${D}${prefix}/lib/rpm/$f
 done
 for i in ${prefix}/share/automake-*/*; do
   if test -f "$i" && test -f ${D}${prefix}/lib/rpm/"${i##*/}"; then
     rm -f ${D}${prefix}/lib/rpm/"${i##*/}"
   fi
 done
 rm -f ${D}${prefix}/lib/*.la
 rm -f ${D}${prefix}/lib/rpm-plugins/*.la
 
 #fdupes ${D}${prefix}/lib/rpm/platform
 
 sh ${D}${prefix}/lib/rpm/find-lang.sh ${D} rpm
 
 
 
}

pkg_postinst_${PN}() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
    test -f ${localstatedir}/lib/rpm/Packages || rpm --initdb
    rm -f ${localstatedir}/lib/rpm/Filemd5s \
          ${localstatedir}/lib/rpm/Filedigests \
          ${localstatedir}/lib/rpm/Requireversion \
          ${localstatedir}/lib/rpm/Provideversion

}

pkg_postrm_${PN}() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig

}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " rpm-security-plugin "
PACKAGES += " python-rpm "
PACKAGES += " rpm-build "
PACKAGES += " rpm-dev "
PACKAGES += " rpm-docs "
PACKAGES += " rpm "

rpm-security-plugin_files = ""
rpm-security-plugin_files += "${prefix}/lib/rpm-plugins/msm.so"
rpm-security-plugin_files += "${prefix}/lib/rpm-plugins/msm-device-sec-policy"
rpm-security-plugin_files += "${sysconfdir}/device-sec-policy"
MANIFESTFILES_${PN}-security-plugin = "rpm.manifest"

python-rpm_files = ""
python-rpm_files += "${prefix}/lib/python2.7/site-packages/rpm"
python-rpm_files += "${prefix}/lib/python2.7/site-packages/rpm/transaction.py"

rpm-build_files = ""
rpm-build_files += "${prefix}/bin/rpmbuild"
rpm-build_files += "${prefix}/bin/gendiff"
rpm-build_files += "${prefix}/bin/rpmspec"
rpm-build_files += "${prefix}/bin/rpmsign"
rpm-build_files += "${prefix}/lib/rpm/tizen/find-*"
rpm-build_files += "${prefix}/lib/rpm/brp-*"
rpm-build_files += "${prefix}/lib/rpm/find-supplements*"
rpm-build_files += "${prefix}/lib/rpm/check-*"
rpm-build_files += "${prefix}/lib/rpm/debugedit"
rpm-build_files += "${prefix}/lib/rpm/find-debuginfo.sh"
rpm-build_files += "${prefix}/lib/rpm/find-lang.sh"
rpm-build_files += "${prefix}/lib/rpm/find-provides.ksyms"
rpm-build_files += "${prefix}/lib/rpm/*provides*"
rpm-build_files += "${prefix}/lib/rpm/*requires*"
rpm-build_files += "${prefix}/lib/rpm/*deps*"
rpm-build_files += "${prefix}/lib/rpm/*.prov"
rpm-build_files += "${prefix}/lib/rpm/*.req"
rpm-build_files += "${prefix}/lib/rpm/macros.*"
rpm-build_files += "${prefix}/lib/rpm/fileattrs"
MANIFESTFILES_${PN}-build = "rpm.manifest"

rpm-dev_files = ""
rpm-dev_files += "${prefix}/bin/rpmgraph"
rpm-dev_files += "${prefix}/include/rpm"
rpm-dev_files += "${prefix}/lib/librpm.so"
rpm-dev_files += "${prefix}/lib/librpmbuild.so"
rpm-dev_files += "${prefix}/lib/librpmio.so"
rpm-dev_files += "${prefix}/lib/librpmsign.so"
rpm-dev_files += "${prefix}/lib/pkgconfig/rpm.pc"
MANIFESTFILES_${PN}-dev = "rpm.manifest"

rpm-docs_files = ""
rpm-docs_files += "GROUPS"

rpm_files = ""
rpm_files += "${sysconfdir}/rpm"
rpm_files += "/bin/rpm"
rpm_files += "${prefix}/bin/rpm2cpio"
rpm_files += "${prefix}/bin/rpmdb"
rpm_files += "${prefix}/bin/rpmkeys"
rpm_files += "${prefix}/bin/rpmquery"
rpm_files += "${prefix}/bin/rpmverify"
rpm_files += "${prefix}/bin/rpmqpack"
rpm_files += "%dir ${prefix}/lib/rpm"
rpm_files += "${prefix}/lib/rpm/macros"
rpm_files += "${prefix}/lib/rpm/macros.d"
rpm_files += "${prefix}/lib/rpm/rpmpopt*"
rpm_files += "${prefix}/lib/rpm/rpmrc"
rpm_files += "${prefix}/lib/rpm/tizen/macros"
rpm_files += "${prefix}/lib/rpm/tizen_macros"
rpm_files += "${prefix}/lib/rpm/rpm.supp"
rpm_files += "${prefix}/lib/rpm/tgpg"
rpm_files += "${prefix}/lib/rpm/platform"
rpm_files += "${prefix}/lib/rpm-plugins"
rpm_files += "${prefix}/lib/rpm-plugins/exec.so"
rpm_files += "${prefix}/lib/librpm.so.*"
rpm_files += "${prefix}/lib/librpmio.so.*"
rpm_files += "${prefix}/lib/librpmbuild.so.*"
rpm_files += "${prefix}/lib/librpmsign.so.*"
rpm_files += "${localstatedir}/lib/rpm"
rpm_files += "%attr(755,root,root) ${prefix}/src/packages/BUILD"
rpm_files += "%attr(755,root,root) ${prefix}/src/packages/SPECS"
rpm_files += "%attr(755,root,root) ${prefix}/src/packages/SOURCES"
rpm_files += "%attr(755,root,root) ${prefix}/src/packages/SRPMS"
rpm_files += "%attr(755,root,root) ${prefix}/src/packages/RPMS"
rpm_files += "%attr(755,root,root) ${prefix}/src/packages/BUILDROOT"
rpm_files += "%attr(755,root,root) ${prefix}/src/packages/RPMS/*"
MANIFESTFILES_${PN} = "rpm.manifest"
DIRFILES_${PN} = ""
DIRFILES_${PN} += "   ${prefix}/lib/rpm-plugins"
DIRFILES_${PN} += "   ${localstatedir}/lib/rpm"
DIRFILES_${PN} += "   %attr(755,root,root) ${prefix}/src/packages/BUILD"
DIRFILES_${PN} += "   %attr(755,root,root) ${prefix}/src/packages/SPECS"
DIRFILES_${PN} += "   %attr(755,root,root) ${prefix}/src/packages/SOURCES"
DIRFILES_${PN} += "   %attr(755,root,root) ${prefix}/src/packages/SRPMS"
DIRFILES_${PN} += "   %attr(755,root,root) ${prefix}/src/packages/RPMS"
DIRFILES_${PN} += "   %attr(755,root,root) ${prefix}/src/packages/BUILDROOT"
DIRFILES_${PN} += "   %attr(755,root,root) ${prefix}/src/packages/RPMS/*"

FILES_${PN}-security-plugin = "${rpm-security-plugin_files}"
FILES_python-${PN} = "${python-rpm_files}"
FILES_${PN}-build = "${rpm-build_files}"
FILES_${PN}-dev = "${rpm-dev_files}"
FILES_${PN}-docs = "${rpm-docs_files}"
FILES_${PN} = "${rpm_files}"

PKG_rpm-security-plugin= "rpm-security-plugin"
PKG_python-rpm= "python-rpm"
PKG_rpm-build= "rpm-build"
PKG_rpm-dev= "rpm-dev"
PKG_rpm-docs= "rpm-docs"
PKG_rpm= "rpm"

require rpm-extraconf.inc

