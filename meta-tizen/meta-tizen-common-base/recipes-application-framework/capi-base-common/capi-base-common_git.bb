require capi-base-common.inc

PRIORITY = "10"

LIC_FILES_CHKSUM ??= "file://${COMMON_LICENSE_DIR}/GPL-2.0;md5=801f80980d171dd6425610833a22dbe6"

SRC_URI += "git://review.tizen.org/platform/core/api/common;tag=eb9d71f344e5222977a48101192494e19e806bdd;nobranch=1"

BBCLASSEXTEND += " native "

