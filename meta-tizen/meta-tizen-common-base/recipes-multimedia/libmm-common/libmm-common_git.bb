require libmm-common.inc

PRIORITY = "10"

LIC_FILES_CHKSUM ??= "file://${COMMON_LICENSE_DIR}/GPL-2.0;md5=801f80980d171dd6425610833a22dbe6"

SRC_URI += "git://review.tizen.org/platform/core/multimedia/libmm-common;tag=c244cbbbb20aac7a2413d630b4c0e1b7a1a31f1f;nobranch=1"

BBCLASSEXTEND += " native "

