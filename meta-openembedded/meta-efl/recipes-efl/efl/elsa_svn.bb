DESCRIPTION = "Login manager for Enlightenment"
DEPENDS = "efreet eina eet ecore elementary"
LICENSE = "GPLv3+"
LIC_FILES_CHKSUM = "file://COPYING;md5=d32239bcb673463ab874e80d47fae504"
SECTION = "e/apps"

inherit e gettext
SRC_URI = "${E_SVN}/trunk/PROTO;module=${SRCNAME};proto=http;scmdata=keep \
  file://0001-pam-use-common-auth-instead-of-system-auth.patch \
  file://xserver-nodm.service \
"
S = "${WORKDIR}/${SRCNAME}"

EXTRA_OECONF = "--with-edje-cc=${STAGING_BINDIR_NATIVE}/edje_cc"

PR = "r2"
PV = "0.0.4+svnr${SRCPV}"
SRCREV = "${EFL_SRCREV}"

do_install_append() {
        install -d ${D}${base_libdir}/systemd/system/
        install -m 0644 ${WORKDIR}/xserver-nodm.service ${D}${base_libdir}/systemd/system/xserver-nodm.service
}

inherit systemd
SYSTEMD_PACKAGES = "${PN}-systemd"
SYSTEMD_SERVICE = "xserver-nodm.service"

PACKAGES =+ "${PN}-systemd"
FILES_${PN}-systemd += "${base_libdir}/systemd"
RDEPENDS_${PN}-systemd += "${PN}"

RDEPENDS_${PN} += "${PN}-themes sessreg xauth"
CONFFILES_${PN} += "${sysconfdir}/elsa.conf"
RCONFLICTS_${PN} += "xserver-nodm-init"
RREPLACES_${PN} += "xserver-nodm-init"
RCONFLICTS_${PN}-systemd += "xserver-nodm-init"
RREPLACES_${PN}-systemd += "xserver-nodm-init"
