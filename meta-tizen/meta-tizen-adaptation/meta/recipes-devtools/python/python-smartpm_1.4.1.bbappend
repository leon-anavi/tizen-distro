FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

SRC_URI_remove = "file://smart-dflags.patch"

DEPENDS_append = " python-rpm-native "

SRC_URI_append = " file://remove_checkrpm_public_key.patch "
SRC_URI_append = " file://0001-No-getArchScore-for-RPM-4.patch "
SRC_URI_append = " file://0001-Ignore-arch-for-RPM-4.patch "
SRC_URI_append = " file://fix-type-cast-of-installed-size.patch "
