require recipes-image/images/tizen-common-imx6.bb

SUMMARY = "A Wayland image with a terminal and crosswalk for Freescale i.MX6"

LICENSE = "MIT"

DESCRIPTION = "A weston image with Tizen:Common."

# Crosswalk
CORE_IMAGE_EXTRA_INSTALL += "packagegroup-tizen-crosswalk"

# Time zone
CORE_IMAGE_EXTRA_INSTALL += "tzdata"
