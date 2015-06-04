require libslp-location.inc

PRIORITY = "10"

LIC_FILES_CHKSUM ??= "file://${COMMON_LICENSE_DIR}/GPL-2.0;md5=801f80980d171dd6425610833a22dbe6"

SRC_URI += "git://review.tizen.org/platform/core/location/libslp-location;tag=0d55b8e4b5b01019c6cfca14541563bd3c1b4f7f;nobranch=1"

BBCLASSEXTEND += " native "

