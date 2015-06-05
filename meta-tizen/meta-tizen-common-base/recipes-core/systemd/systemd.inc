DESCRIPTION = "A System and Service Manager"
HOMEPAGE = "http://www.freedesktop.org/wiki/Software/systemd"
SECTION = "Base/Startup"
LICENSE = "LGPL-2.0+ and MIT and GPL-2.0+"
PV = "216"

SRC_URI = ""

S = "${WORKDIR}/git"

inherit manifest autotools-brokensep

BBCLASSEXTEND = ""
PROVIDES = ""

#PROVIDES by libsystemd
PROVIDES += "libsystemd"


#PROVIDES by systemd
# the PROVIDES rules is ignore "SysVinit = 2.86-24"
PROVIDES += "SysVinit"
RPROVIDES_systemd += "SysVinit"
# the PROVIDES rules is ignore "sysvinit = 2.86-24"
PROVIDES += "sysvinit"
RPROVIDES_systemd += "sysvinit"
# the PROVIDES rules is ignore "/bin/systemctl  "
PROVIDES += "/bin/systemctl"
RPROVIDES_systemd += "/bin/systemctl"
# the PROVIDES rules is ignore "/sbin/shutdown  "
PROVIDES += "/sbin/shutdown"
RPROVIDES_systemd += "/sbin/shutdown"
# the PROVIDES rules is ignore "udev = 216"
PROVIDES += "udev"
RPROVIDES_systemd += "udev"


#PROVIDES by libgudev-dev
PROVIDES += "libgudev-dev"


#PROVIDES by systemd-dev
PROVIDES += "systemd-dev"
# the PROVIDES rules is ignore "libudev-dev = 216"
PROVIDES += "libudev-dev"
RPROVIDES_systemd-dev += "libudev-dev"


#PROVIDES by libgudev
PROVIDES += "libgudev"


#PROVIDES by systemd-docs
PROVIDES += "systemd-docs "


#PROVIDES by systemd-analyze
PROVIDES += "systemd-analyze"


RDEPENDS = ""
#RDEPENDS of systemd (${PN})
RDEPENDS_${PN} += "hwdata"
RDEPENDS_${PN} += "dbus"
RDEPENDS_${PN} += "gawk"
RDEPENDS_${PN} += "coreutils"
RDEPENDS_${PN} += "shadow"
RDEPENDS_${PN} += "glibc"

#RDEPENDS of libgudev-dev (libgudev-dev)
RDEPENDS_libgudev-dev += "libgudev"

#RDEPENDS of systemd-dev (${PN}-dev)
RDEPENDS_${PN}-dev += "libsystemd"
RDEPENDS_${PN}-dev += "systemd"

#RDEPENDS of libgudev (libgudev)
RDEPENDS_libgudev += "systemd"

#RDEPENDS of systemd-analyze (${PN}-analyze)
RDEPENDS_${PN}-analyze += "systemd"


DEPENDS = ""
#DEPENDS of systemd
DEPENDS += "kmod"
DEPENDS_append_class-native = " intltool-native"
DEPENDS_append_class-target = " intltool-native"
DEPENDS += "gperf"
DEPENDS += "hwdata"
DEPENDS += "dbus"
DEPENDS += "usbutils"
inherit pkgconfig
DEPENDS += "acl"
DEPENDS += "docbook-xsl-stylesheets"
DEPENDS += "glib-2.0"
DEPENDS += "libxslt"
DEPENDS += "pciutils"
DEPENDS += "libcap"
DEPENDS += "util-linux"
DEPENDS += "libgcrypt"
DEPENDS += "xz"
DEPENDS += "libpam"

do_prep() {
 cd ${S}
 chmod -Rf a+rX,u+w,g-w,o-w ${S}
 #setup -q
 cp ${S}/packaging/systemd.manifest .
 
 
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
  
  if which gtkdocize >/dev/null 2>/dev/null; then
          gtkdocize --docdir docs/ --flavour no-tmpl
          gtkdocargs=--enable-gtk-doc
  else
          echo "You don't have gtk-doc installed, and thus won't be able to generate the documentation."
          rm -f docs/gtk-doc.make
          echo 'EXTRA_DIST =' > docs/gtk-doc.make
  fi
  
  intltoolize --force --automake
  
  autotools_do_configure
  
  oe_runmake ${PARALLEL_MAKE}
  
  
  
}
EXTRA_OECONF += " --disable-kdbus --enable-compat-libs --enable-bootchart --disable-sysusers --disable-firstboot --disable-timesyncd --disable-resolved --disable-networkd --libexecdir=${prefix}/lib --docdir=${prefix}/share/doc/packages/systemd --disable-static --disable-libcurl --with-sysvinit-path= --with-sysvrcnd-path= --with-smack-run-label=System --with-rootprefix=/ --with-rootlibdir=/lib cc_cv_CFLAGS__flto=no"

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
 
 #find_lang systemd
 cat <<EOF >> systemd.lang
 %lang(fr) ${prefix}/lib/systemd/catalog/systemd.fr.catalog
 %lang(it) ${prefix}/lib/systemd/catalog/systemd.it.catalog
 %lang(ru) ${prefix}/lib/systemd/catalog/systemd.ru.catalog
EOF
 
 # udev links
 mkdir -p ${D}${prefix}/sbin
 ln -sf ../bin/udevadm ${D}${prefix}/sbin/udevadm
 mkdir -p ${D}${prefix}/lib/firmware/updates
 
 # Create SysV compatibility symlinks. systemctl/systemd are smart
 # enough to detect in which way they are called.
 ln -sf /lib/systemd/systemd ${D}${prefix}/sbin/init
 ln -sf /lib/systemd/systemd ${D}${prefix}/bin/systemd
 ln -sf ../bin/systemctl ${D}${prefix}/sbin/reboot
 ln -sf ../bin/systemctl ${D}${prefix}/sbin/halt
 ln -sf ../bin/systemctl ${D}${prefix}/sbin/poweroff
 ln -sf ../bin/systemctl ${D}${prefix}/sbin/shutdown
 ln -sf ../bin/systemctl ${D}${prefix}/sbin/telinit
 ln -sf ../bin/systemctl ${D}${prefix}/sbin/runlevel
 
 # legacy links
 ln -sf loginctl ${D}${prefix}/bin/systemd-loginctl
 
 # We create all wants links manually at installation time to make sure
 # they are not owned and hence overriden by rpm after the used deleted
 # them.
 rm -rf ${D}${sysconfdir}/systemd/system/*.target.wants
 
 # Make sure the ghost-ing below works
 touch ${D}${sysconfdir}/systemd/system/runlevel2.target
 touch ${D}${sysconfdir}/systemd/system/runlevel3.target
 touch ${D}${sysconfdir}/systemd/system/runlevel4.target
 touch ${D}${sysconfdir}/systemd/system/runlevel5.target
 
 # Make sure these directories are properly owned
 mkdir -p ${D}${systemd_unitdir}/system/basic.target.wants
 mkdir -p ${D}${systemd_unitdir}/system/default.target.wants
 mkdir -p ${D}${systemd_unitdir}/system/dbus.target.wants
 mkdir -p ${D}${systemd_unitdir}/system/syslog.target.wants
 
 # Make sure the user generators dir exists too
 mkdir -p ${D}/lib/systemd/system-generators
 mkdir -p ${D}${prefix}/lib/systemd/user-generators
 
 # Create new-style configuration files so that we can ghost-own them
 touch ${D}${sysconfdir}/hostname
 touch ${D}${sysconfdir}/vconsole.conf
 touch ${D}${sysconfdir}/locale.conf
 touch ${D}${sysconfdir}/machine-id
 touch ${D}${sysconfdir}/machine-info
 touch ${D}${sysconfdir}/timezone
 
 mkdir -p ${D}/lib/systemd/system-preset/
 mkdir -p ${D}/lib/systemd/user-preset/
 
 # Make sure the shutdown/sleep drop-in dirs exist
 mkdir -p ${D}/lib/systemd/system-shutdown/
 mkdir -p ${D}/lib/systemd/system-sleep/
 
 # Make sure the NTP units dir exists
 mkdir -p ${D}${prefix}/lib/systemd/ntp-units.d/
 
 # Install modprobe fragment
 mkdir -p ${D}${sysconfdir}/modprobe.d/
 
 # Fix the dangling /var/lock -> /run/lock symlink
 install -Dm644 tmpfiles.d/legacy.conf ${D}${prefix}/lib/tmpfiles.d/legacy.conf
 
 install -m644 ${S}/packaging/pamconsole-tmp.conf ${D}${prefix}/lib/tmpfiles.d/
 
 rm -rf ${D}${systemd_unitdir}/system/default.target
 install -m 755 -d ${D}${systemd_unitdir}/system
 install -m 644 ${S}/packaging/default.target ${D}${systemd_unitdir}/system/
 
 rm -rf ${D}${prefix}/share/doc/packages/systemd
 
 # Disable some useless services in Tizen
 rm -rf ${D}${prefix}/lib/systemd/user/sysinit.target.wants/dev-hugepages.mount
 rm -rf ${D}${prefix}/lib/systemd/user/sysinit.target.wants/sys-fs-fuse-connections.mount
 rm -rf ${D}${prefix}/lib/systemd/user/sysinit.target.wants/systemd-binfmt.service
 rm -rf ${D}${prefix}/lib/systemd/user/sysinit.target.wants/systemd-modules-load.service
 rm -rf ${D}${prefix}/lib/systemd/user/sysinit.target.wants/systemd-ask-password-console.path
 rm -rf ${D}${prefix}/lib/systemd/user/multi-user.target.wants/systemd-ask-password-wall.path
 
 # Move macros to the proper location for Tizen
 mkdir -p ${D}${sysconfdir}/rpm
 install -m644 src/core/macros.systemd ${D}${sysconfdir}/rpm/macros.systemd
 
 rm -fr ${D}${prefix}/lib/rpm
 rm -fr ${D}${sysconfdir}/kernel
 rm -fr ${D}${sysconfdir}/modprobe.d
 rm -fr ${D}${localstatedir}
 
 # Exclude ELF binaries
 rm -f ${D}/lib/systemd/system-generators/systemd-debug-generator
 rm -f ${D}${prefix}/lib/systemd/system-generators/systemd-hibernate-resume-generator
 
 # end of install
 
 
}

pkg_preinst_${PN}() {
    #!/bin/sh -e

    getent group cdrom >/dev/null   2>&1 || groupadd -r -g 11 cdrom   >/dev/null 2>&1 || :
    getent group tape >/dev/null    2>&1 || groupadd -r -g 33 tape    >/dev/null 2>&1 || :
    getent group dialout >/dev/null 2>&1 || groupadd -r -g 18 dialout >/dev/null 2>&1 || :
    getent group floppy >/dev/null  2>&1 || groupadd -r -g 19 floppy  >/dev/null 2>&1 || :
    systemctl stop systemd-udevd-control.socket systemd-udevd-kernel.socket systemd-udevd.service >/dev/null 2>&1 || :
    # Rename configuration files that changed their names
    mv -n $D${sysconfdir}/systemd/systemd-logind.conf $D${sysconfdir}/systemd/logind.conf >/dev/null 2>&1 || :
    mv -n $D${sysconfdir}/systemd/systemd-journald.conf $D${sysconfdir}/systemd/journald.conf >/dev/null 2>&1 || :

}

pkg_postinst_${PN}() {
    #!/bin/sh -e

    systemd-machine-id-setup > /dev/null 2>&1 || :
    systemd-random-seed save > /dev/null 2>&1 || :
    systemctl daemon-reexec > /dev/null 2>&1 || :
    systemctl start systemd-udevd.service >/dev/null 2>&1 || :

}

pkg_postinst_libgudev() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postinst_libsystemd() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_prerm_${PN}() {
    #!/bin/sh -e

    if [ $1 -eq 0 ] ; then
            systemctl disable \
                    getty@.service \
                    remote-fs.target \
                    systemd-readahead-replay.service \
                    systemd-readahead-collect.service >/dev/null 2>&1 || :
    fi

}

pkg_postrm_libgudev() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_libsystemd() {
    #!/bin/sh -e

    [ "x$D" == "x" ] && ldconfig
}

pkg_postrm_${PN}() {
    #!/bin/sh -e

    if [ $1 -ge 1 ] ; then
            systemctl daemon-reload > /dev/null 2>&1 || :
            systemctl try-restart systemd-logind.service >/dev/null 2>&1 || :
    fi

}

PACKAGES = "${PN}-dbg ${PN}-doc ${PN}-locale"
PACKAGES += " libsystemd "
PACKAGES += " systemd "
PACKAGES += " libgudev-dev "
PACKAGES += " systemd-dev "
PACKAGES += " systemd-docs "
PACKAGES += " libgudev "
PACKAGES += " systemd-analyze "

libsystemd_files = ""
libsystemd_files += "/lib/security/pam_systemd.so"
libsystemd_files += "/lib/libsystemd.so.*"
libsystemd_files += "/lib/libudev.so.*"
libsystemd_files += "/lib/libsystemd-daemon.so.*"
libsystemd_files += "/lib/libsystemd-id128.so.*"
libsystemd_files += "/lib/libsystemd-journal.so.*"
libsystemd_files += "/lib/libsystemd-login.so.*"
libsystemd_files += "${prefix}/lib/libnss_myhostname.so.2"
libsystemd_files += "${prefix}/lib/libnss_mymachines.so.2"
MANIFESTFILES_lib${PN} = "systemd.manifest"

systemd_files = ""
systemd_files += "${sysconfdir}/pam.d/systemd-user"
systemd_files += "${prefix}/bin/bootctl"
systemd_files += "${prefix}/bin/busctl"
systemd_files += "${prefix}/bin/kernel-install"
systemd_files += "/bin/machinectl"
systemd_files += "${prefix}/bin/systemd-run"
systemd_files += "${prefix}/lib/kernel"
systemd_files += "${prefix}/lib/kernel/install.d"
systemd_files += "${prefix}/lib/kernel/install.d/50-depmod.install"
systemd_files += "${prefix}/lib/kernel/install.d/90-loaderentry.install"
systemd_files += "${prefix}/bin/hostnamectl"
systemd_files += "${prefix}/bin/localectl"
systemd_files += "${prefix}/bin/coredumpctl"
systemd_files += "${prefix}/bin/timedatectl"
systemd_files += "${sysconfdir}/systemd"
systemd_files += "${sysconfdir}/systemd/system"
systemd_files += "${sysconfdir}/systemd/user"
systemd_files += "${sysconfdir}/tmpfiles.d"
systemd_files += "${sysconfdir}/sysctl.d"
systemd_files += "${sysconfdir}/modules-load.d"
systemd_files += "${sysconfdir}/binfmt.d"
systemd_files += "${prefix}/share/bash-completion/*"
systemd_files += "${prefix}/share/zsh/site-functions"
systemd_files += "${prefix}/share/zsh/site-functions/*"
systemd_files += "${sysconfdir}/udev"
systemd_files += "${sysconfdir}/udev/rules.d"
systemd_files += "/lib/systemd"
systemd_files += "${systemd_unitdir}/system"
systemd_files += "/lib/systemd/system-generators"
systemd_files += "${prefix}/lib/systemd/user-generators"
systemd_files += "/lib/systemd/system-preset"
systemd_files += "/lib/systemd/user-preset"
systemd_files += "/lib/systemd/system-shutdown"
systemd_files += "/lib/systemd/system-sleep"
systemd_files += "${prefix}/lib/tmpfiles.d"
systemd_files += "${prefix}/lib/sysctl.d"
systemd_files += "${prefix}/lib/modules-load.d"
systemd_files += "${prefix}/lib/binfmt.d"
systemd_files += "${prefix}/lib/firmware"
systemd_files += "${prefix}/lib/firmware/updates"
systemd_files += "${prefix}/share/systemd"
systemd_files += "${prefix}/lib/systemd/ntp-units.d"
systemd_files += "${sysconfdir}/dbus-1/system.d/org.freedesktop.systemd1.conf"
systemd_files += "${sysconfdir}/dbus-1/system.d/org.freedesktop.hostname1.conf"
systemd_files += "${sysconfdir}/dbus-1/system.d/org.freedesktop.login1.conf"
systemd_files += "${sysconfdir}/dbus-1/system.d/org.freedesktop.locale1.conf"
systemd_files += "${sysconfdir}/dbus-1/system.d/org.freedesktop.timedate1.conf"
systemd_files += "${sysconfdir}/dbus-1/system.d/org.freedesktop.machine1.conf"
systemd_files += "${sysconfdir}/systemd/bootchart.conf"
systemd_files += "${sysconfdir}/systemd/coredump.conf"
systemd_files += "${sysconfdir}/systemd/system.conf"
systemd_files += "${sysconfdir}/systemd/user.conf"
systemd_files += "${sysconfdir}/systemd/logind.conf"
systemd_files += "${sysconfdir}/systemd/journald.conf"
systemd_files += "${sysconfdir}/udev/udev.conf"
systemd_files += "${sysconfdir}/xdg/systemd"
systemd_files += "${prefix}/bin/systemd"
systemd_files += "/bin/systemctl"
systemd_files += "/bin/systemd-notify"
systemd_files += "/bin/systemd-ask-password"
systemd_files += "/bin/systemd-tty-ask-password-agent"
systemd_files += "/bin/systemd-machine-id-setup"
systemd_files += "/bin/loginctl"
systemd_files += "${prefix}/bin/systemd-loginctl"
systemd_files += "/bin/journalctl"
systemd_files += "/bin/systemd-tmpfiles"
systemd_files += "${prefix}/bin/systemd-nspawn"
systemd_files += "${prefix}/bin/systemd-stdio-bridge"
systemd_files += "${prefix}/bin/systemd-cat"
systemd_files += "${prefix}/bin/systemd-cgls"
systemd_files += "${prefix}/bin/systemd-cgtop"
systemd_files += "${prefix}/bin/systemd-delta"
systemd_files += "${prefix}/bin/systemd-detect-virt"
systemd_files += "/bin/systemd-inhibit"
systemd_files += "/bin/udevadm"
systemd_files += "/bin/systemd-escape"
systemd_files += "${prefix}/bin/systemd-path"
systemd_files += "${prefix}/lib/sysctl.d/*.conf"
systemd_files += "/lib/systemd/systemd"
systemd_files += "${systemd_unitdir}/system"
systemd_files += "${systemd_unitdir}/system/basic.target.wants"
systemd_files += "${prefix}/lib/systemd/user"
systemd_files += "/lib/systemd/network"
systemd_files += "${prefix}/lib/systemd/user/basic.target"
systemd_files += "${prefix}/lib/systemd/user/bluetooth.target"
systemd_files += "${prefix}/lib/systemd/user/exit.target"
systemd_files += "${prefix}/lib/systemd/user/printer.target"
systemd_files += "${prefix}/lib/systemd/user/shutdown.target"
systemd_files += "${prefix}/lib/systemd/user/sockets.target"
systemd_files += "${prefix}/lib/systemd/user/sound.target"
systemd_files += "${prefix}/lib/systemd/user/systemd-exit.service"
systemd_files += "${prefix}/lib/systemd/user/paths.target"
systemd_files += "${prefix}/lib/systemd/user/smartcard.target"
systemd_files += "${prefix}/lib/systemd/user/timers.target"
systemd_files += "${prefix}/lib/systemd/user/busnames.target"
systemd_files += "${prefix}/lib/systemd/user/default.target"
systemd_files += "/lib/systemd/network/99-default.link"
systemd_files += "/lib/systemd/systemd-*"
systemd_files += "${prefix}/lib/systemd/catalog"
systemd_files += "${prefix}/lib/systemd/catalog/systemd.catalog"
systemd_files += "/lib/udev"
systemd_files += "/lib/systemd/system-generators/systemd-efi-boot-generator"
systemd_files += "/lib/systemd/system-generators/systemd-getty-generator"
systemd_files += "/lib/systemd/system-generators/systemd-fstab-generator"
systemd_files += "/lib/systemd/system-generators/systemd-system-update-generator"
systemd_files += "/lib/systemd/system-generators/systemd-gpt-auto-generator"
systemd_files += "${prefix}/lib/tmpfiles.d/systemd.conf"
systemd_files += "${prefix}/lib/tmpfiles.d/x11.conf"
systemd_files += "${prefix}/lib/tmpfiles.d/tmp.conf"
systemd_files += "${prefix}/lib/tmpfiles.d/legacy.conf"
systemd_files += "${prefix}/lib/tmpfiles.d/pamconsole-tmp.conf"
systemd_files += "${prefix}/lib/tmpfiles.d/systemd-nologin.conf"
systemd_files += "${prefix}/lib/tmpfiles.d/etc.conf"
systemd_files += "${prefix}/lib/tmpfiles.d/var.conf"
systemd_files += "${prefix}/sbin/init"
systemd_files += "${prefix}/sbin/reboot"
systemd_files += "${prefix}/sbin/halt"
systemd_files += "${prefix}/sbin/poweroff"
systemd_files += "${prefix}/sbin/shutdown"
systemd_files += "${prefix}/sbin/telinit"
systemd_files += "${prefix}/sbin/runlevel"
systemd_files += "${prefix}/sbin/udevadm"
systemd_files += "${prefix}/share/systemd/kbd-model-map"
systemd_files += "${prefix}/share/dbus-1/services/org.freedesktop.systemd1.service"
systemd_files += "${prefix}/share/dbus-1/system-services/org.freedesktop.systemd1.service"
systemd_files += "${prefix}/share/dbus-1/system-services/org.freedesktop.hostname1.service"
systemd_files += "${prefix}/share/dbus-1/system-services/org.freedesktop.login1.service"
systemd_files += "${prefix}/share/dbus-1/system-services/org.freedesktop.locale1.service"
systemd_files += "${prefix}/share/dbus-1/system-services/org.freedesktop.timedate1.service"
systemd_files += "${prefix}/share/dbus-1/system-services/org.freedesktop.machine1.service"
systemd_files += "${prefix}/share/polkit-1"
systemd_files += "${prefix}/share/polkit-1/actions"
systemd_files += "${prefix}/share/polkit-1/actions/org.freedesktop.systemd1.policy"
systemd_files += "${prefix}/share/polkit-1/actions/org.freedesktop.hostname1.policy"
systemd_files += "${prefix}/share/polkit-1/actions/org.freedesktop.login1.policy"
systemd_files += "${prefix}/share/polkit-1/actions/org.freedesktop.locale1.policy"
systemd_files += "${prefix}/share/polkit-1/actions/org.freedesktop.timedate1.policy"
CONFFILES_${PN} = ""
CONFFILES_${PN} += "${sysconfdir}/pam.d/systemd-user"
MANIFESTFILES_${PN} = "systemd.manifest"
DIRFILES_${PN} = ""
DIRFILES_${PN} += "${prefix}/lib/kernel"
DIRFILES_${PN} += "${prefix}/lib/kernel/install.d"
DIRFILES_${PN} += "${sysconfdir}/systemd"
DIRFILES_${PN} += "${sysconfdir}/systemd/system"
DIRFILES_${PN} += "${sysconfdir}/systemd/user"
DIRFILES_${PN} += "${sysconfdir}/tmpfiles.d"
DIRFILES_${PN} += "${sysconfdir}/sysctl.d"
DIRFILES_${PN} += "${sysconfdir}/modules-load.d"
DIRFILES_${PN} += "${sysconfdir}/binfmt.d"
DIRFILES_${PN} += "${prefix}/share/zsh/site-functions"
DIRFILES_${PN} += "${sysconfdir}/udev"
DIRFILES_${PN} += "${sysconfdir}/udev/rules.d"
DIRFILES_${PN} += "/lib/systemd"
DIRFILES_${PN} += "${systemd_unitdir}/system"
DIRFILES_${PN} += "/lib/systemd/system-generators"
DIRFILES_${PN} += "${prefix}/lib/systemd/user-generators"
DIRFILES_${PN} += "/lib/systemd/system-preset"
DIRFILES_${PN} += "/lib/systemd/user-preset"
DIRFILES_${PN} += "/lib/systemd/system-shutdown"
DIRFILES_${PN} += "/lib/systemd/system-sleep"
DIRFILES_${PN} += "${prefix}/lib/tmpfiles.d"
DIRFILES_${PN} += "${prefix}/lib/sysctl.d"
DIRFILES_${PN} += "${prefix}/lib/modules-load.d"
DIRFILES_${PN} += "${prefix}/lib/binfmt.d"
DIRFILES_${PN} += "${prefix}/lib/firmware"
DIRFILES_${PN} += "${prefix}/lib/firmware/updates"
DIRFILES_${PN} += "${prefix}/share/systemd"
DIRFILES_${PN} += "${prefix}/lib/systemd/ntp-units.d"
DIRFILES_${PN} += "${systemd_unitdir}/system/basic.target.wants"
DIRFILES_${PN} += "${prefix}/lib/systemd/user"
DIRFILES_${PN} += "/lib/systemd/network"
DIRFILES_${PN} += "${prefix}/lib/systemd/catalog"
DIRFILES_${PN} += "${prefix}/share/polkit-1"
DIRFILES_${PN} += "${prefix}/share/polkit-1/actions"

libgudev-dev_files = ""
libgudev-dev_files += "${prefix}/lib/libgudev-1.0.so"
libgudev-dev_files += "${prefix}/include/gudev-1.0"
libgudev-dev_files += "${prefix}/include/gudev-1.0/gudev"
libgudev-dev_files += "${prefix}/include/gudev-1.0/gudev/*.h"
libgudev-dev_files += "${prefix}/lib/pkgconfig/gudev-1.0*"
MANIFESTFILES_libgudev-dev = "systemd.manifest"
DIRFILES_libgudev-dev = ""
DIRFILES_libgudev-dev += "${prefix}/include/gudev-1.0"
DIRFILES_libgudev-dev += "${prefix}/include/gudev-1.0/gudev"

systemd-dev_files = ""
systemd-dev_files += "${prefix}/lib/libudev.so"
systemd-dev_files += "${prefix}/lib/libsystemd.so"
systemd-dev_files += "${prefix}/lib/libsystemd-daemon.so"
systemd-dev_files += "${prefix}/lib/libsystemd-id128.so"
systemd-dev_files += "${prefix}/lib/libsystemd-journal.so"
systemd-dev_files += "${prefix}/lib/libsystemd-login.so"
systemd-dev_files += "${prefix}/include/systemd"
systemd-dev_files += "${prefix}/include/systemd/_sd-common.h"
systemd-dev_files += "${prefix}/include/systemd/sd-daemon.h"
systemd-dev_files += "${prefix}/include/systemd/sd-id128.h"
systemd-dev_files += "${prefix}/include/systemd/sd-journal.h"
systemd-dev_files += "${prefix}/include/systemd/sd-login.h"
systemd-dev_files += "${prefix}/include/systemd/sd-messages.h"
systemd-dev_files += "${prefix}/include/libudev.h"
systemd-dev_files += "${prefix}/lib/pkgconfig/libudev.pc"
systemd-dev_files += "${prefix}/lib/pkgconfig/libsystemd.pc"
systemd-dev_files += "${prefix}/lib/pkgconfig/libsystemd-daemon.pc"
systemd-dev_files += "${prefix}/lib/pkgconfig/libsystemd-id128.pc"
systemd-dev_files += "${prefix}/lib/pkgconfig/libsystemd-journal.pc"
systemd-dev_files += "${prefix}/lib/pkgconfig/libsystemd-login.pc"
systemd-dev_files += "${prefix}/share/pkgconfig/systemd.pc"
systemd-dev_files += "${prefix}/share/pkgconfig/udev.pc"
systemd-dev_files += "${sysconfdir}/rpm/macros.systemd"
CONFFILES_${PN}-dev = ""
CONFFILES_${PN}-dev += "${sysconfdir}/rpm/macros.systemd"
MANIFESTFILES_${PN}-dev = "systemd.manifest"
DIRFILES_${PN}-dev = ""
DIRFILES_${PN}-dev += "${prefix}/include/systemd"

systemd-docs_files = ""

libgudev_files = ""
libgudev_files += "${prefix}/lib/libgudev-1.0.so.*"
MANIFESTFILES_libgudev = "systemd.manifest"

systemd-analyze_files = ""
systemd-analyze_files += "${prefix}/bin/systemd-analyze"
MANIFESTFILES_${PN}-analyze = "systemd.manifest"

FILES_lib${PN} = "${libsystemd_files}"
FILES_${PN} = "${systemd_files}"
FILES_libgudev-dev = "${libgudev-dev_files}"
FILES_${PN}-dev = "${systemd-dev_files}"
FILES_${PN}-docs = "${systemd-docs_files}"
FILES_libgudev = "${libgudev_files}"
FILES_${PN}-analyze = "${systemd-analyze_files}"

PKG_libsystemd= "libsystemd"
PKG_systemd= "systemd"
PKG_libgudev-dev= "libgudev-dev"
PKG_systemd-dev= "systemd-dev"
PKG_systemd-docs= "systemd-docs"
PKG_libgudev= "libgudev"
PKG_systemd-analyze= "systemd-analyze"

require systemd-extraconf.inc

