require capi-media-wav-player.inc

PRIORITY = "10"

LIC_FILES_CHKSUM ??= "file://${COMMON_LICENSE_DIR}/GPL-2.0;md5=801f80980d171dd6425610833a22dbe6"

SRC_URI += "git://review.tizen.org/platform/core/api/wav-player;tag=1607cdbbb1fa3f0d1c1bc47b14a7d16d94ca815c;nobranch=1"

BBCLASSEXTEND += " native "

