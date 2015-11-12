require CommonAPI-DBus.inc

PRIORITY = "10"

LIC_FILES_CHKSUM ??= "file://${COMMON_LICENSE_DIR}/GPL-2.0;md5=801f80980d171dd6425610833a22dbe6"

SRC_URI += "git://review.tizen.org/profile/ivi/common-api-dbus-runtime;tag=a1dd3cf92c548e65b3a8bd2b83f35902a5450a6d;nobranch=1 \
            file://avoid-segfault-on-added-signal.patch \
           "

BBCLASSEXTEND += " native "

