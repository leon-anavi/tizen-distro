require capi-content-media-content.inc

PRIORITY = "10"

LIC_FILES_CHKSUM ??= "file://${COMMON_LICENSE_DIR}/GPL-2.0;md5=801f80980d171dd6425610833a22dbe6"

SRC_URI += "git://review.tizen.org/platform/core/api/media-content;tag=af69336d70625b89d376c9b1fa90225eb2deed95;nobranch=1"

BBCLASSEXTEND += " native "

